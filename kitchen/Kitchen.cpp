/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "deps/KitchenStatus.hpp"

const millisec_t Kitchen::__timeout = 5000;

const std::unordered_map<std::string_view, Kitchen::commandInfo_t> Kitchen::__commands = {
    { "HELP",
        { &Kitchen::_cmdHelp, 1, 0, ": show this on stderr only." }
    },
    { "START",
        { &Kitchen::_cmdStart, 4, 4, "<multiplier> <cooks> <refill_rate_ms>: Initialize a kitchen." }
    },
    { "NEW_RECIPE",
        { &Kitchen::_cmdNewRecipe, 4, 0, "<name> <cook_time_ms> [<ingredient> <amount>]...: Add a pizza recipe to the menu." }
    },
    { "ORDER",
        { &Kitchen::_cmdOrder, 3, 3, "<name> <size>: Start cooking a pizza." }
    },
    { "STATUS",
        { &Kitchen::_cmdStatus, 1, 2, "[<any>]: Get the status of the kitchen. If <any> is present, data will be serialized." }
    },
    { "STOP",
        { &Kitchen::_cmdStop, 1, 0, ": Close kitchen." }
    }
};

Kitchen::Kitchen(std::unique_ptr<IPCProtocol> &IPC, const std::string_view &logFile)
    : _IPC(std::move(IPC))
    , _logStream(std::make_shared<Log>())
    , _fridge(std::make_shared<Fridge>())
    , _orderQueue(std::make_shared<OrderQueue>())
    , _running(false)
    , _cookTimeMultiplier(0)
    , _maxOrderQueue(0)
{
    _logStream->open(logFile);
}

Kitchen::~Kitchen()
{
    _IPC = nullptr;
    stop();
    _manager.join();
}

void Kitchen::start()
{
    commandPtr_t cmd = nullptr;
    std::vector<std::string> argv;

    _running = true;
    std::string responseMsg;
    while (_running && _IPC->receive(argv)) {
        if (!_running)
            break;
        cmd = _validateCommand(argv);
        if (!cmd)
            continue;
        responseMsg.clear();
        if (!(this->*cmd)(argv, responseMsg)) {
            _errorResponse(responseMsg, argv);
        } else {
            _successResponse(responseMsg);
        }
    }
}

void Kitchen::stop()
{
    _running = false;
    _fridge->stop();
    _orderQueue->close();
}

Kitchen::commandPtr_t Kitchen::_validateCommand(const argv_t &argv)
{
    if (argv.size() == 0) {
        _errorResponse("Invalid empty command", argv);
        return (nullptr);
    }
    const auto &command = Kitchen::__commands.find(argv[0]);
    if (command == Kitchen::__commands.end()) {
        _errorResponse("Unknown command", argv);
        return (nullptr);
    }
    const auto &info = command->second;
    if (argv.size() < info.minArgc || (info.maxArgc != 0 && argv.size() > info.maxArgc)) {
        _errorResponse("Invalid command syntax", argv);
        return (nullptr);
    }
    return (info.cmdPtr);
}

void Kitchen::_errorResponse(const std::string_view &message, const argv_t &failedCmd)
{
    _IPC->send("KO", message);
    #ifdef DEBUG
        if (failedCmd.size() == 0)
            return;
        std::cerr << "\t";
        for (const auto &it : failedCmd)
            std::cerr << it << " ";
        std::cerr << std::endl;
    #endif
}

void Kitchen::_successResponse(const std::string &message)
{
    _IPC->send("OK", message);
}

void Kitchen::_startManager()
{
    _manager.run([&]() {
        std::unique_ptr<Clock> timer;

        while (_running) {
            if (timer != nullptr && timer->getElapsedMillisecond() >= __timeout) {
                #ifdef DEBUG
                    _errorResponse("kitchen closed for inactivity, press enter to leave...");
                #endif
                stop();
                return;
            }
            _fridge->tryRestock();
            _orderQueue->removeCookedPizzas();
            const auto &cook = std::find_if(_cooks.cbegin(), _cooks.cend(), [](const auto &it) {
                return (it->isCooking());
            });

            if (cook != _cooks.cend())
                timer = nullptr;
            else if (timer == nullptr)
                timer = std::make_unique<Clock>();

        }
    });
}

bool Kitchen::_cmdHelp(const argv_t &argv, std::string &responseMsg)
{
    for (const auto &it : Kitchen::__commands)
        std::cout << "\t" << it.first << " " << it.second.usage << std::endl;
    return (true);
}

bool Kitchen::_cmdStart(const argv_t &argv, std::string &responseMsg)
{
    static bool started = false;

    if (started) {
        responseMsg = "kitchen already started";
        return (false);
    }
    responseMsg = "invalid arguments";
    try {
        size_t read = 0;

        const float multiplier = std::stof(argv[1], &read);
        if (read < argv[1].size() || multiplier < 0)
            return (false);

        size_t maxCooks = std::stoul(argv[2], &read);
        if (read < argv[2].size() || maxCooks == 0)
            return (false);

        const millisec_t restockRate = std::stol(argv[3], &read);
        if (read < argv[3].size())
            return (false);

        _cookTimeMultiplier = multiplier;
        _maxOrderQueue = maxCooks * 2;
        _fridge->start(restockRate);
        for (; maxCooks > 0; --maxCooks) {
            _cooks.emplace_back(std::make_unique<Cook>(_orderQueue, _fridge, _cookTimeMultiplier, _logStream));
            _cooks.back()->start();
        }
        _startManager();
    } catch (...) {
        return (false);
    }
    responseMsg.clear();
    started = true;
    return (true);
}

bool Kitchen::_cmdNewRecipe(const argv_t &argv, std::string &responseMsg)
{
    if ((argv.size() % 2) == 0) {
        responseMsg = "incorrect amount of argument";
        return (false);
    }
    responseMsg = "invalid format";
    try {
        size_t read = 0;
        millisec_t cookTime = std::stol(argv[2], &read);
        if (read < argv[2].size())
            return (false);
        Pizza pizza(argv[1], cookTime);

        auto it = argv.begin() + 3;
        auto end = argv.end();
        size_t amount = 0;
        for (; it != end; it += 2) {
            amount = std::stoul(*(it + 1));
            if (!amount)
                continue;
            pizza.addIngredientToRecipe(Ingredient(*it, amount));
            if (!_fridge->isKnownIngredient(*it))
                _fridge->newIngredient(*it);
        }
        _recipe.emplace_back(std::move(pizza));
    } catch (...) {
        return (false);
    }
    responseMsg.clear();
    return (true);
}

bool Kitchen::_cmdOrder(const argv_t &argv, std::string &responseMsg)
{
    if (_orderQueue->getSize() >= _maxOrderQueue) {
        responseMsg = "order queue already at maximum capacity (" + std::to_string(_maxOrderQueue) + ")";
        return (false);
    }
    int size = 0;
    responseMsg = "invalid pizza size";
    try {
        size = std::stoi(argv[2]);
    } catch (...) {
        return (false);
    }
    if (size < int(pizzaSize_t::S) || size > int(pizzaSize_t::XXL))
        return (false);
    for (const auto &it : _recipe) {
        if (it.getName() == argv[1]) {
            _orderQueue->addOrder(it, pizzaSize_t(size));
            responseMsg.clear();
            return (true);
        }
    }
    responseMsg = "unknown pizza";
    return (false);
}

bool Kitchen::_cmdStatus(const argv_t &argv, std::string &responseMsg)
{
    KitchenStatus status;

    status.orderQueueCapacity = _maxOrderQueue;
    status.totalCooks = _cooks.size();
    for (const auto &it : _cooks) {
        if (it->isCooking())
            ++status.activeCooks;
    }
    for (const auto &it : _orderQueue->getQueue()) {
        if (it.getStatus() != Pizza::COOKED)
            status.orderQueue.emplace_back(it.getName(), it.getSize(), it.getStatus());
    }
    if (argv.size() > 1) {
        responseMsg = status.serialize();
    } else {
        status.dump(std::cout);
    }
    return (true);
}

bool Kitchen::_cmdStop(const argv_t &argv, std::string &responseMsg)
{
    stop();
    return (true);
}

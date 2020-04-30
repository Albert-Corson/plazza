/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

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
        { &Kitchen::_cmdOrder, 2, 2, "<name>: Start cooking a pizza." }
    },
    { "STOP",
        { &Kitchen::_cmdStop, 1, 0, ": Close kitchen." }
    }
};

Kitchen::Kitchen(std::unique_ptr<IPCProtocol> &IPC, std::ostream &logOut)
    : _IPC(std::move(IPC))
    , _logOut(logOut)
    , _fridge(std::make_shared<Fridge>())
    , _orderQueue(std::make_shared<OrderQueue>())
    , _running(false)
    , _cookTimeMultiplier(0)
    , _maxOrderQueue(0)
{
}

Kitchen::~Kitchen()
{
    _fridge->stop();
    _orderQueue->close();
}

void Kitchen::start()
{
    commandPtr_t cmd = nullptr;
    std::vector<std::string> argv;

    _running = true;
    while (_running && _IPC->receive(argv)) {
        cmd = _validateCommand(argv);
        if (!cmd)
            continue;
        if (!(this->*cmd)(argv)) {
            _errorResponse("Command failed", argv);
        } else {
            _successResponse();
        }
    }
}

void Kitchen::stop()
{
    _cmdStop();
}

Kitchen::commandPtr_t Kitchen::_validateCommand(const argv_t &argv)
{
    if (argv.size() == 0) {
        _errorResponse("Invalid empty command, quitting", argv);
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

void Kitchen::_successResponse()
{
    _IPC->send("OK");
}

void Kitchen::_errorResponse(const std::string_view &message, const argv_t &failedCmd)
{
    _IPC->send("KO:", message);
    if (failedCmd.size() == 0)
        return;
    std::cerr << "\t";
    for (const auto &it : failedCmd)
        std::cerr << it << " ";
    std::cerr << std::endl;
}

bool Kitchen::_cmdHelp(const argv_t &argv)
{
    for (const auto &it : Kitchen::__commands)
        std::cerr << "\t" << it.first << " " << it.second.usage << std::endl;
    return (true);
}

bool Kitchen::_cmdStart(const argv_t &argv)
{
    try {
        size_t read = 0;

        const float multiplier = std::stof(argv[1], &read);
        if (read < argv[1].size())
            return (false);

        size_t maxCooks = std::stoul(argv[2], &read);
        if (read < argv[2].size())
            return (false);

        const millisec_t restockRate = std::stol(argv[3], &read);
        if (read < argv[3].size())
            return (false);

        _cookTimeMultiplier = multiplier;
        _maxOrderQueue = maxCooks;
        _fridge->start(restockRate);
        for (; maxCooks > 0; --maxCooks) {
            _cooks.emplace_back(std::make_unique<Cook>(_orderQueue, _fridge, _cookTimeMultiplier, _logOut));
            _cooks.back()->start();
        }
    } catch (...) {
        return (false);
    }
    return (true);
}

bool Kitchen::_cmdNewRecipe(const argv_t &argv)
{
    if ((argv.size() % 2) == 0)
        return (false);
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
    return (true);
}

bool Kitchen::_cmdOrder(const argv_t &argv)
{
    if (_orderQueue->getSize() > _maxOrderQueue)
        return (false);
    for (const auto &it : _recipe) {
        if (it.getName() == argv[1]) {
            _orderQueue->addOrder(it);
            return (true);
        }
    }
    return (false);
}

bool Kitchen::_cmdStop(const argv_t &argv)
{
    _running = false;
    return (true);
}

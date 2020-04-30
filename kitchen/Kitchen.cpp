/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

const std::unordered_map<std::string_view, Kitchen::commandInfo_t> Kitchen::__commands = {
    { "HELP",
        { &Kitchen::_help, 1, 0, ": show this on stderr only." }
    },
    { "START",
        { &Kitchen::_start, 4, 4, "<multiplier> <cooks> <refill_rate_ms>: Initialize a kitchen." }
    },
    { "NEW_RECIPE",
        { &Kitchen::_newRecipe, 4, 0, "<name> <cook_time_ms> [<ingredient> <amount>]...: Add a pizza recipe to the menu." }
    },
    { "ORDER",
        { &Kitchen::_order, 2, 2, "<name>: Start cooking a pizza." }
    },
    { "STOP",
        { &Kitchen::_stop, 1, 0, ": Close kitchen." }
    }
};

Kitchen::Kitchen(std::unique_ptr<IPCProtocol> &IPC)
    : _IPC(std::move(IPC))
    , _fridge(std::make_shared<Fridge>())
    , _orderQueue(std::make_shared<OrderQueue>())
    , _running(false)
    , _cookTimeMultiplier(0)
    , _maxOrderQueue(0)
{
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
    _stop();
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

bool Kitchen::_help(const argv_t &argv)
{
    for (const auto &it : Kitchen::__commands)
        std::cerr << "\t" << it.first << " " << it.second.usage << std::endl;
    return (true);
}

bool Kitchen::_start(const argv_t &argv)
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
            _cooks.emplace_back(_orderQueue, _fridge, _cookTimeMultiplier);
            _cooks.back().start();
        }
    } catch (...) {
        return (false);
    }
    return (true);
}

bool Kitchen::_newRecipe(const argv_t &argv)
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
        for (; it != end; it += 2) {
            pizza.addIngredientToRecipe(Ingredient(*it, std::stoul(*(it + 1))));
            if (!_fridge->isKnownIngredient(*it))
                _fridge->newIngredient(*it);
        }
        _recipe.emplace_back(std::move(pizza));
    } catch (...) {
        return (false);
    }
    return (true);
}

bool Kitchen::_order(const argv_t &argv)
{
    for (const auto &it : _recipe) {
        if (it.getName() == argv[1])
            _orderQueue->addOrder(it);
    }
    return (false);
}

bool Kitchen::_stop(const argv_t &argv)
{
    _running = false;
    return (true);
}

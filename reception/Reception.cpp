/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** reception
*/

#include <iostream>
#include <string>
#include <regex>

#include "Reception.hpp"
#include "KitchenSpawner/IKitchenLink.hpp"
#include "deps/utils/StringUtils.hpp"
#include "logfile.hpp"

const std::unordered_map<std::string_view, Reception::commandPtr_t> Reception::__commands = {
    { "exit", &Reception::_cmdExit },
    { "status", &Reception::_cmdStatus },
    { "connect", &Reception::_cmdConnect },
};

Reception::Reception(unsigned int timeMultiplier, unsigned int cooksPerKitchen, unsigned int restoreDelay)
    : _running(false)
    , _pizzaMenu("./pizzas")
    , _kitchenManager(std::make_unique<KitchenManager>(timeMultiplier, cooksPerKitchen, restoreDelay, _pizzaMenu))
{
    if (!OLogStream::makeFile(LOGFILE))
        std::cerr << "Error: couldn't create log file `" << LOGFILE << "`, using stdout" << std::endl;
    _logStream.open(LOGFILE);
    _logStream.log("Reception started");
    _kitchenManager->bindSpawner(std::make_shared<KitchenProcessSpawner>());
}

Reception::~Reception()
{
    _kitchenManager = nullptr;
    _logStream.log("Recpetion closed\n");
}

void Reception::start(void)
{
    std::string buffer;

    _running = true;
    while (_running) {
        std::cout << "$> ";
        if (!std::getline(std::cin, buffer))
            break;
        if (!_parseCmd(buffer))
            _parseOrders(buffer);
    }
}

bool Reception::_parseCmd(const std::string &buffer)
{
    std::vector<std::string> args;

    StringUtils::strtab(buffer, args);
    if (!args.size())
        return (true);
    for (const auto &it : __commands) {
        if (it.first == args[0]) {
            (this->*it.second)(args);
            return (true);
        }
    }
    return (false);
}

void Reception::_parseOrders(std::string &buffer)
{
    std::regex format("^[ \\t]*([A-Za-z0-9]+)[ \\t]+(S|M|L|XL|XXL)[ \\t]+x([0-9]+)[ \\t]*");
    std::smatch matches;
    size_t pos = 0;

    while (buffer.size()) {
        if (std::regex_search(buffer, matches, format)) {
            _tempPizzaName = matches.str(1);
            _tempPizzaSize = Pizza::getSizeFromStr(matches.str(2));
            _tempPizzaOrder = std::stoi(matches.str(3));
            if (_tempPizzaSize == Pizza::SZ_UNDEF || !_pizzaMenu.isGoodPizzaName(_tempPizzaName))
                std::cerr << "Error: invalid command `" << buffer.substr(0, buffer.find(';')) << "`" << std::endl;
            else
                _sendToKitchen();
            buffer = buffer.substr(matches.str(0).size());
        } else {
            std::cerr << "Error: invalid command `" << buffer.substr(0, buffer.find(';')) << "`" << std::endl;
        }
        pos = buffer.find(';');
        if (pos == std::string::npos)
            break;
        buffer = buffer.substr(pos + 1);
    }
}

void Reception::_sendToKitchen(void)
{
    std::vector<std::string> args;

    while (_tempPizzaOrder > 0) {
        --_tempPizzaOrder;
        auto &kitchen = _kitchenManager->queryKitchen();
        auto &ipc = kitchen.getIPC();

        ipc.send("ORDER", _tempPizzaName, _tempPizzaSize);
        ipc.receive(args);
        if (args[0] == "OK")
            continue;
        for (const auto &it : args)
            std::cout << it << " ";
        std::cout << std::endl;
    }
}

void Reception::_cmdExit(const argv_t &args)
{
    _running = false;
}

void Reception::_cmdStatus(const argv_t &args)
{
    _kitchenManager->dump();
}

void Reception::_cmdConnect(const argv_t &args)
{
}
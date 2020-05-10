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
#include "deps/utils/StringUtils.hpp"
#include "logfile.hpp"

Reception::Reception(unsigned int timeMultiplier, unsigned int cooksPerKitchen, unsigned int restoreDelay)
    : _pizzaMenu("./pizzas")
    , _kitchenManager(timeMultiplier, cooksPerKitchen, restoreDelay, _pizzaMenu)
{
    if (!OLogStream::makeFile(LOGFILE))
        std::cerr << "Error: couldn't create log file `" << LOGFILE << "`, using stdout" << std::endl;
    _logStream.open(LOGFILE);
    _logStream.log("Reception started");
    _kitchenManager.bindSpawner(std::make_shared<KitchenProcessSpawner>());
}

Reception::~Reception() 
{
    _logStream.log("Recpetion closed\n");
}

void Reception::parseOrders(std::string buffer)
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
                sendToKitchen();
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

void Reception::start(void)
{
    std::string buffer;

    std::cout << "$> ";
    while (std::getline(std::cin, buffer)) {
        if (buffer == "exit") {
            break;
        } else if (buffer == "status") {
            _kitchenManager.dump();
        } else {
            this->parseOrders(buffer);
        }
        std::cout << "$> ";
    }
}

void Reception::sendToKitchen(void)
{
    std::vector<std::string> args;

    while (_tempPizzaOrder > 0) {
        --_tempPizzaOrder;
        auto &kitchen = _kitchenManager.queryKitchen();
        auto &ipc = kitchen.getIPC();

        ipc.send("ORDER", _tempPizzaName, _tempPizzaSize);
        ipc.receive(args);
        for (const auto &it : args) {
            std::cout << it << " ";
        }
        std::cout << std::endl;
    }
}

/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** reception
*/

#include "Reception.hpp"
#include "deps/utils/StringUtils.hpp"
#include <iostream>
#include <string>
#include <regex>

void Reception::parseCli(std::string buffer)
{
    std::regex format("^[ \\t]*([A-Za-z0-9]+)[ \\t]+(S|M|L|XL|XXL)[ \\t]+x([0-9]+)[ \\t]*");
    std::smatch matches;
    bool err = false;
    size_t pos = 0;

    while (buffer.size()) {
        if (std::regex_search(buffer, matches, format)) {
            _tempPizzaName = matches.str(1);
            _tempPizzaSize = Pizza::getSizeFromStr(matches.str(2));
            _tempPizzaOrder = std::stoi(matches.str(3));
            if (_tempPizzaSize == Pizza::SZ_UNDEF || !_pizzaMenu.isGoodPizzaName(_tempPizzaName))
                err = true;
            else
                sendToKitchen();
            buffer = buffer.substr(matches.str(0).size());
        } else {
            err = true;
        }
        pos = buffer.find(';');
        if (pos == std::string::npos)
            break;
        buffer[pos] = ' ';
    }
    if (err) {
        std::cerr << "Error: one or more invalid command" << std::endl;
    } else {
        std::cout << "Command OK" << std::endl;
    }
}

void Reception::start(void)
{
    std::string buffer;

    while (std::getline(std::cin, buffer)) {
        this->parseCli(buffer);
    }
}

void Reception::sendToKitchen(void)
{
    std::vector<std::string> args;

    while (_tempPizzaOrder > 0) {
        std::cout << "Data to send " << _tempPizzaName << " " <<  _tempPizzaSize << std::endl;
        --_tempPizzaOrder;
        auto &kitchen = _kitchenManager.queryKitchen();
        auto &ipc = kitchen.getIPC();

        ipc.send("ORDER pizza2 4");
        ipc.receive(args);
    }
}
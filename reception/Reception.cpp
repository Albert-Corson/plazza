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

static bool is_num(char const *arg)
{
    std::string str(arg);

    for (const auto &it : str) {
        if (it < '0' || it > '9')
            return (false);
    }
    return (true);
}

int Reception::parseCli(std::string buffer)
{
    std::vector<std::string> parsed;
    StringUtils::strtab(buffer, parsed);
    unsigned long int index = 1;
    int nb_words = 0;
    bool err = false;

    for (const auto &it : parsed) {
        ++nb_words;
        if (!err) {
            if (nb_words == 1) {
                if (_pizzaMenu.isGoodPizzaName(it))
                    _tempPizzaName = it;
                else
                    err = true;
            } else if (nb_words == 2) {
                if (Pizza::getSizeFromStr(it) == Pizza::SZ_UNDEF)
                    err = true;
                else
                    _tempPizzaSize = Pizza::getSizeFromStr(it);
            } else if (nb_words == 3) {
                if (it.at(0) == 'x' && is_num(it.substr(1).c_str()))
                    _tempPizzaOrder = std::stoi(it.substr(1));
                else if (it.at(0) == 'x' && it.at(it.size() - 1) == ';' && is_num(it.substr(1, it.size() - 2).c_str()) && index != parsed.size())
                    _tempPizzaOrder = std::stoi(it.substr(1, it.size() - 2).c_str());
                else
                    err = true;
            }
            if (nb_words == 3 && !err) {
                this->sendToKitchen();
                nb_words = 0;
                err = false;
            }
            if (it.find(';') < it.size()) {
                nb_words = 0;
                err = false;
            }
        }
        ++index;
    }
    return (0);
}

int Reception::start(void)
{
    std::string buffer;

    while (std::getline(std::cin, buffer)) {
        this->parseCli(buffer);
    }
    return (0);
}

int Reception::sendToKitchen(void)
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
    return (0);
}
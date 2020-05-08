/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ParsePizzas
*/

#include <string>
#include <iostream>

#include "Reception.hpp"
#include "deps/Exception.hpp"
#include "deps/IPC/NamedPipe.hpp"
#include "deps/IPC/IPCProtocol.hpp"
#include "KitchenSpawner/process/KitchenProcessSpawner.hpp"
#include "KitchenManager/KitchenManager.hpp"
#include "deps/plazza/pizzaSize.hpp"

static bool is_num(const std::string &str)
{
    long unsigned int index = 0;

    while (index < str.size()) {
        if (str.at(index) < '0' || str.at(index) > '9')
            return 0;
        ++index;
    }
    return 1;
}

int Reception::parse_pizza(std::string command)
{
    static std::string name = "";
    static std::string size = "";
    static int nb_order = 0;
    static int nb_words = 0;

    ++nb_words;
    if (!Reception::_pizzas.is_new_pizza(command)) {
        name = command;
        return 0;
    }
    if (this->_pizzas.is_size_good(command)) {
        size = command;
        return 0;
    }
    if (command.at(0) == 'x') {
        if (command.at(command.size() - 1) == ';' && is_num(command.substr(1, command.size() - 2)))
            nb_order = std::stoi(command.substr(1, command.size() - 2));
        else if (is_num(command.substr(1, command.size() - 1)))
            nb_order = std::stoi(command.substr(1, command.size() - 1));
    }
    if (nb_words == 3 && name != "" && size != "" && nb_order != 0)
        std::cout << "Send to Kitchen Informations !" << std::endl;
    if (nb_words >= 3) {
        nb_words = 0;
        name = "";
        size = "";
        nb_order = 0;
    }
    return 0;
}
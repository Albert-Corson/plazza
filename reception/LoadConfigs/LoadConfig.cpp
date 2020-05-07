/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** LoadConfig
*/

#include <iostream>
#include <fstream>
#include "Reception.hpp"

static void filter_line(std::string line, Pizza &pizzas)
{
    if (line.at(0) == '#')
        return;
    if (line.at(0) == '!') {
        pizzas.add_new_pizza(line.substr(1));
        return;
    }
    if (line.at(0) == '?') {
        try {
            pizzas.add_second_multiplier_to_pizza(std::stoi(line.substr(1)));
        } catch (...) {
            throw (84);
        }
        return;
    }
    if (pizzas.is_new_ingredient_to_list(line)) {
        pizzas.add_ingredient_to_list(line);
    }
    pizzas.add_new_ingredient_to_pizza(line);
}

int Reception::load_config(void)
{
    std::ifstream file;
    std::string line;

    file.open("pizzas.conf");
    if (!file)
        return 84;
    while (std::getline(file, line)) {
        filter_line(line, this->_pizzas);
    }
    file.close();
    return 0;
}
/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main_reception
*/

#ifndef MAIN_RECEPTION_HPP_
#define MAIN_RECEPTION_HPP_

#include <string>
#include <memory>
#include "ParsePizzas.hpp"

class Reception
{
    public:
        int load_args(int argc, char const **argv);
        int parse_pizza(std::string command);
        int load_config(void);
    protected:
        unsigned int _timeMultiplier;
        unsigned int _cooksPerKitchen;
        unsigned int _restoreDelay;
        Pizza _pizzas;
};

#endif /* !MAIN_RECEPTION_HPP_ */
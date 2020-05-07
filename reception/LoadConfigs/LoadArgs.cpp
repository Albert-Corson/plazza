/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** LoadArgs
*/

#include "Reception.hpp"
#include <string>

static int is_num(char const *arg)
{
    std::string str(arg);
    long unsigned int index = 0;

    while (index < str.size()) {
        if (str.at(index) < '0' || str.at(index) < '9')
            return (84);
        ++index;
    }
    return 0;
}

int Reception::load_args(int argc, char const **argv)
{   
    if (argc != 4)
        throw (84);
    if (!is_num(argv[1]) || !is_num(argv[2]) || !is_num(argv[3]))
        throw (84);
    _timeMultiplier = std::stoi(std::string(argv[1]));
    _cooksPerKitchen = std::stoi(std::string(argv[2]));
    _restoreDelay = std::stoi(std::string(argv[3]));
    return 0;
}
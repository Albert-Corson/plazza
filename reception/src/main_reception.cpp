/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main_reception
*/

#include <iostream>

#include "main_reception.hpp"

int main_reception(int argc, char const **argv)
{
    Reception panel;
    std::string line = "";

    if (panel.load_args(argc, argv) != 0 || panel.load_config() != 0)
        throw (84);
    while (1 && line != "exit")
    {
        std::cin >> line;
        if (std::cin.eof())
            return 0;
        panel.parse_pizza(line);
    }
    
    return 0;
}
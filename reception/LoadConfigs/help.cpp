/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** help
*/

#include <iostream>

static void help(const char *binName)
{
    std::cerr << "USAGE: " << binName << " <multiplier> <cooks> <refill>" << std::endl
              << "\tmultiplier\tcooking time multiplier" << std::endl
              << "\tcooks\tnumber of cooks per kitchen" << std::endl
              << "\trefill\ttime interval between ingredients stocks refills (in ms)" << std::endl;
}
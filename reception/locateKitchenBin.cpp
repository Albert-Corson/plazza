/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** locateKitchenBin
*/

#include "locateKitchenBin.hpp"

const std::string &locateKitchenBin(const char *newLocation)
{
    static std::string location = "bin/kitchen";

    if (newLocation)
        location = newLocation;
    return (location);
}

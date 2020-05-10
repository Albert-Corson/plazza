/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** locateKitchenBin
*/

#include <filesystem>
#include <unistd.h>

#include "locateKitchenBin.hpp"

const std::string &locateKitchenBin(const char *newLocation)
{
    static std::string location = "bin/kitchen";

    if (newLocation)
        location = newLocation;
    return (location);
}

void updateKitchenBinLocation()
{
    char buffer[1024];
    if (readlink("/proc/self/exe", buffer, 1024) < 0)
        return;
    std::filesystem::path path(buffer);
    path.replace_filename("kitchen");
    locateKitchenBin(path.c_str());
}

/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main
*/

#include <iostream>

#include "Reception.hpp"
#include "locateKitchenBin.hpp"

static void help(const char *binName)
{
    std::cerr << "USAGE: " << binName << " <multiplier> <cooks> <refill>" << std::endl
              << "\tmultiplier\tcooking time multiplier" << std::endl
              << "\tcooks\tnumber of cooks per kitchen" << std::endl
              << "\trefill\ttime interval between ingredients stocks refills (in ms)" << std::endl;
}

int main(int argc, char const *argv[])
{
    unsigned long timeMultiplier = 0;
    unsigned long cooksPerKitchen = 0;
    unsigned long restoreDelay = 0;

    if (argc != 4) {
        if (argc == 2 && !std::strcmp(argv[1], "-h")) {
            help(argv[0]);
            return (0);
        } else {
            return (84);
        }
    }
    updateKitchenBinLocation();
    try {
        timeMultiplier = std::stoul(std::string(argv[1]));
        cooksPerKitchen = std::stoul(std::string(argv[2]));
        restoreDelay = std::stoul(std::string(argv[3]));
        Reception reception(timeMultiplier, cooksPerKitchen, restoreDelay);
        reception.start();
    } catch (const std::exception &err) {
        std::cerr << "Reception fatal error:" << std::endl
                  << "\t" << err.what() << std::endl;
        return (84);
    } catch (...) {
        std::cerr << "Reception fatal error" << std::endl;
        return (84);
    }
    return (0);
}

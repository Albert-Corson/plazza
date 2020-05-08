/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** reception
*/

#include <iostream>

#include "Reception.hpp"

int reception(int argc, char const **argv)
{
    // Reception panel;
    // std::string line = "";

    // if (panel.load_args(argc, argv) != 0 || panel.load_config() != 0)
    //     throw (84);
    // while (1 && line != "exit")
    // {
    //     std::cin >> line;
    //     if (std::cin.eof())
    //         return 0;
    //     panel.parse_pizza(line);
    // }
    return 0;
}

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

    // KitchenManager manager(multiplier, cooks, interval);
    // manager.bindSpawner(std::make_shared<KitchenProcessSpawner>());

    // std::string command;
    // std::vector<std::string> args;
    // while (std::cin >> command) {
    //     auto &kitchen = manager.queryKitchen();
    //     auto &ipc = kitchen.getIPC();
    //     ipc.send("ORDER pizza2 4");
    //     ipc.receive(args);
    // }
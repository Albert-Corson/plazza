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
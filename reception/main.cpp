/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main
*/

#include <iostream>
#include "deps/Exception.hpp"
#include "deps/IPC/NamedPipe.hpp"
#include "deps/IPC/IPCProtocol.hpp"
#include "KitchenSpawner/process/KitchenProcessSpawner.hpp"
#include "KitchenManager/KitchenManager.hpp"
#include "deps/pizzaSize.hpp"

static void help(const char *binName)
{
    std::cerr << "USAGE: " << binName << " <multiplier> <cooks> <refill>" << std::endl
              << "\tmultiplier\tcooking time multiplier" << std::endl
              << "\tcooks\tnumber of cooks per kitchen" << std::endl
              << "\trefill\ttime interval between ingredients stocks refills (in ms)" << std::endl;
}

int main(int argc, char const *argv[])
{
    if (argc != 4) {
        help(argv[0]);
        return (84);
    }
    float multiplier = std::stof(argv[1]);
    int cooks = std::stod(argv[2]);
    int interval = std::stod(argv[3]);

    KitchenManager manager(multiplier, cooks, interval);
    manager.bindSpawner(std::make_shared<KitchenProcessSpawner>());

    std::string command;
    std::vector<std::string> args;
    while (std::cin >> command) {
        auto &kitchen = manager.queryKitchen();
        auto &ipc = kitchen.getIPC();
        ipc.send("ORDER pizza2 4");
        ipc.receive(args);
    }
    return (0);
}
/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main
*/

#include "KitchenManager/KitchenManager.hpp"
#include "KitchenSpawner/process/KitchenProcessSpawner.hpp"

int main(int argc, char const *argv[])
{
    float multiplier = std::stof(argv[1]);
    int cooks = std::stod(argv[2]);
    int interval = std::stod(argv[3]);

    KitchenManager manager(multiplier, cooks, interval);
    manager.bindSpawner(std::make_shared<KitchenProcessSpawner>());

    std::string command;
    std::vector<std::string> args;
    while (std::cin >> command) {
        manager.resetCache();
        auto &kitchen = manager.queryKitchen();
        auto &ipc = kitchen.getIPC();
        ipc.send("ORDER pizza2 4");
        ipc.receive(args);
    }
    return (0);
}
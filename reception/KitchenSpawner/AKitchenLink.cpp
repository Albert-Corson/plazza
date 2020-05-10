/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** AKitchenLink
*/

#include <memory>
#include <vector>
#include <string>
#include "deps/plazza/KitchenStatus.hpp"
#include "KitchenSpawner/AKitchenLink.hpp"

bool AKitchenLink::start(float multiplier, int cooks, int interval,
                         const std::vector<Pizza> &pizzaMenu)
{
    std::vector<std::string> args;

    _ipc.send("START", std::to_string(multiplier), std::to_string(cooks), std::to_string(interval));
    if (!_ipc.receive(args) || args[0] != "OK")
        return (false);
    for (const auto &pizza : pizzaMenu) {
        std::string recipe = "NEW_RECIPE "
            + pizza.getName() + " "
            + std::to_string(pizza.getCookTime());

        for (const auto &ingredient : pizza.getRecipe())
            recipe += " \"" + ingredient.getName() + "\" "
                + std::to_string(ingredient.getAmount());

        _ipc.send(recipe);
        if (!_ipc.receive(args) || args[0] != "OK")
            return (false);
    }
    return (true);
}

void AKitchenLink::stop()
{
    if (this->isAlive()) {
        std::vector<std::string> args;

        _ipc.send("STOP");
        if (!_ipc.receive(args) || args[0] != "OK") {
            std::cerr << "Failed to stop kitchen. Killing." << std::endl;
            this->kill();
        }
        this->waitstop();
    }
}

unsigned int AKitchenLink::getAvailability()
{
    if (!this->isAlive())
        return (false);
    std::vector<std::string> args;
    KitchenStatus status;
    _ipc.send("STATUS serialized");
    if (!_ipc.receive(args) || args[0] != "OK")
        return (false);
    status.deserialize(args, 1);
    return (status.orderQueueCapacity - status.orderQueue.size());
}

bool AKitchenLink::isAvailable()
{
    return (this->getAvailability() > 0);
}

IPCProtocol &AKitchenLink::getIPC()
{
    return (_ipc);
}

void AKitchenLink::setIPC(IPCProtocol &ipc)
{
    _ipc = ipc;
}
/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** AKitchenLink
*/

#include <memory>
#include <vector>
#include <string>
#include "deps/KitchenStatus.hpp"
#include "KitchenSpawner/AKitchenLink.hpp"

bool AKitchenLink::start(float multiplier, int cooks, int interval)
{
    std::vector<std::string> pizzas = {
        "pizza2 2000 a 1 b 2 c 3",
        "pizza10 10000 a 5 b 1 d 2",
        "pizza15 15000 a 10"
    };

    std::vector<std::string> args;

    _ipc.send("START "
              + std::to_string(multiplier) + " "
              + std::to_string(cooks) + " "
              + std::to_string(interval));
    if (!_ipc.receive(args) || args[0] != "OK")
        return (false);
    for (const auto &pizza : pizzas) {
        _ipc.send("NEW_RECIPE " + pizza);
        if (!_ipc.receive(args) || args[0] != "OK")
            return (false);
    }
    return (true);
}

void AKitchenLink::stop() const
{
    if (this->isAlive()) {
        std::vector<std::string> args;

        _ipc.send("STOP");
        if (!_ipc.receive(args) || args[0] != "OK") {
            std::cerr << "Failed to stop kitchen." << std::endl;
        }
        this->waitstop();
    }
}

unsigned int AKitchenLink::getAvailability() const
{
    if (!this->isAlive())
        return (false);
    std::vector<std::string> args;
    KitchenStatus status;
    _ipc.send("STATUS serialized");
    if (!_ipc.receive(args) || args[0] != "OK")
        return (false);
    args.erase(args.begin());
    args >> status;
    return (status.orderQueueCapacity - status.orderQueue.size());
}

bool AKitchenLink::isAvailable() const
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
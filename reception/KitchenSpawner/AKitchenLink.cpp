/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** AKitchenLink
*/

#include <memory>
#include <vector>
#include <string>
#include "AKitchenLink.hpp"

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

void AKitchenLink::stop()
{
    if (this->isAlive()) {
        std::vector<std::string> args;

        _ipc.send("STOP");
        if (!_ipc.receive(args) || args[0] != "OK") {
            std::cerr << "Failed to stop kitchen." << std::endl;
        }
    } else {
        std::cerr << "Kitchen closed unexpectedly." << std::endl;
    }
}

bool AKitchenLink::isAvailable() const
{
    if (!this->isAlive())
        return (false);

    std::vector<std::string> args;
    _ipc.send("STATUS serialized");
    if (!_ipc.receive(args) || args[0] != "OK")
        return (false);
    int cooksBusy = std::stoi(args[1]);
    int cooksTotal = std::stoi(args[2]);
    // int queueMax = std::stoi(args[3]);
    if (cooksBusy < cooksTotal)
        return (true);
    return (false);
}

IPCProtocol &AKitchenLink::getIPC()
{
    return (_ipc);
}

void AKitchenLink::setIPC(IPCProtocol &ipc)
{
    _ipc = ipc;
}
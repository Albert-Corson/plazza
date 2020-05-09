/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IKitchenLink
*/

#pragma once

#include "deps/IPC/IPCProtocol.hpp"
#include "deps/plazza/Pizza.hpp"

class IKitchenLink
{
public:
    virtual ~IKitchenLink() = default;

    virtual bool start(float multiplier, int cooks, int interval,
                       const std::vector<Pizza> &pizzaMenu) = 0;
    virtual void waitstop() = 0;
    virtual void stop() = 0;
    virtual bool isAlive() = 0;
    virtual unsigned int getAvailability() = 0;
    virtual bool isAvailable() = 0;

    virtual IPCProtocol &getIPC() = 0;
    virtual void setIPC(IPCProtocol &ipc) = 0;
};
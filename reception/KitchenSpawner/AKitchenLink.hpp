/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** AKitchenLink
*/

#pragma once

#include <memory>
#include "deps/IPC/IPCProtocol.hpp"
#include "IKitchenLink.hpp"

class AKitchenLink : public IKitchenLink
{
public:
    virtual ~AKitchenLink() override = default;

    bool start(float multiplier, int cooks, int interval,
               const std::vector<Pizza> &pizzaMenu) override final;
    virtual void waitstop() override{};
    void stop() override final;
    virtual bool isAlive() = 0;
    unsigned int getAvailability() override final;
    bool isAvailable() override final;

    IPCProtocol &getIPC() override final;
    void setIPC(IPCProtocol &ipc) override final;

protected:
    IPCProtocol _ipc;
};
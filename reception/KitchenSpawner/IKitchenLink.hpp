/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IKitchenLink
*/

#pragma once

#include "deps/IPC/IPCProtocol.hpp"

class IKitchenLink
{
  public:
    virtual ~IKitchenLink() = default;

    virtual bool start(float multiplier, int cooks, int interval) = 0;
    virtual void waitstop() const = 0;
    virtual void stop() const = 0;
    virtual bool isAlive() const = 0;
    virtual bool isAvailable() const = 0;

    virtual IPCProtocol &getIPC() = 0;
    virtual void setIPC(IPCProtocol &ipc) = 0;
};
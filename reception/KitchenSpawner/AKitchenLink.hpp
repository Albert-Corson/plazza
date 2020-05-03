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

    bool start(float multiplier, int cooks, int interval) override final;
    virtual void waitstop() const override{};
    void stop() const override final;
    virtual bool isAlive() const = 0;
    bool isAvailable() const override final;

    IPCProtocol &getIPC() override final;
    void setIPC(IPCProtocol &ipc) override final;

  protected:
    IPCProtocol _ipc;
};
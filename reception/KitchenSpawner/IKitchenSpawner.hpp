/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IKitchenSpawner
*/

#pragma once

#include "deps/IPC/IPCProtocol.hpp"
#include "IKitchenLink.hpp"

class IKitchenSpawner
{
  public:
    virtual ~IKitchenSpawner() = default;

    virtual std::shared_ptr<IKitchenLink> spawn(float multiplier, int cooks, int interval) = 0;
};
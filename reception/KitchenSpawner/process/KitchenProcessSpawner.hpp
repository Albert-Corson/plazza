/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenProcessSpawner
*/

#pragma once

#include <vector>
#include "KitchenSpawner/IKitchenSpawner.hpp"
#include "deps/Process.hpp"
#include "deps/IPC/IPCProtocol.hpp"
#include "deps/Exception.hpp"

class KitchenProcessSpawner : public IKitchenSpawner
{
  public:
    class Exception : public ::Exception
    {
      public:
        Exception(const std::string &msg)
            : ::Exception("KitchenProcessSpawner::Exception: " + msg)
        {
        }
        ~Exception() override = default;
    };

    KitchenProcessSpawner() = default;
    ~KitchenProcessSpawner() = default;

    std::shared_ptr<IKitchenLink> spawn(float multiplier, int cooks, int interval) override final;
};

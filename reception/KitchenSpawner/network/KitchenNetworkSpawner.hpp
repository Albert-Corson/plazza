/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenNetworkSpawner
*/

#pragma once

#include <vector>
#include "KitchenSpawner/IKitchenSpawner.hpp"
#include "deps/Process.hpp"
#include "deps/IPC/IPCProtocol.hpp"
#include "deps/Exception.hpp"
#include "deps/Socket.hpp"

class KitchenNetworkSpawner : public IKitchenSpawner
{
  public:
    class Exception : public ::Exception
    {
      public:
        Exception(const std::string &msg)
            : ::Exception("KitchenNetworkSpawner::Exception: " + msg)
        {
        }
        ~Exception() override = default;
    };

    KitchenNetworkSpawner() = default;
    ~KitchenNetworkSpawner() = default;

    std::shared_ptr<IKitchenLink> spawn(float multiplier, int cooks, int interval,
                                        const std::vector<Pizza> &pizzaMenu) override final;

  private:
    Socket _interface;
};

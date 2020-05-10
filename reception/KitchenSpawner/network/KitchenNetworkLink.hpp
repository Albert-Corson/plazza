/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenNetworkLink
*/

#pragma once

#include <memory>
#include "deps/Socket.hpp"
#include "deps/IPC/Network.hpp"
#include "deps/IPC/IPCProtocol.hpp"
#include "KitchenSpawner/AKitchenLink.hpp"

class KitchenNetworkLink : public AKitchenLink
{
public:
    KitchenNetworkLink(const std::string &address, in_port_t port, pid_t pid);
    ~KitchenNetworkLink() override final = default;

    void waitstop() override final;
    bool isAlive() override final;
    bool kill() override final;

    Network &getNetwork();

protected:
    pid_t   _id;
    Network _network;
    Socket  _interface;
};
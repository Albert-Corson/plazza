/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenProcessLink
*/

#pragma once

#include <memory>
#include "deps/Process.hpp"
#include "deps/IPC/IPCProtocol.hpp"
#include "KitchenSpawner/AKitchenLink.hpp"

class KitchenProcessLink : public AKitchenLink
{
  public:
    KitchenProcessLink(const std::string &fifoName) ;
    ~KitchenProcessLink() override final = default;

    void waitstop() override final;
    bool isAlive() override final;
    Process &getProcess();

protected:
    Process _process;
};
/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenManager
*/

#pragma once

#include <vector>
#include <memory>
#include "deps/Exception.hpp"
#include "KitchenSpawner/IKitchenSpawner.hpp"

class KitchenManager
{
  public:
    class Exception : public ::Exception
    {
      public:
        Exception(const std::string &msg)
            : ::Exception("KitchenManager::Exception: " + msg)
        {
        }
        ~Exception() override = default;
    };

    KitchenManager(float multiplier, int cooks, int interval);
    ~KitchenManager();

    void bindSpawner(std::shared_ptr<IKitchenSpawner> spawner);
    IKitchenLink &queryKitchen();

  private:
    float _multiplier;
    int _cooks;
    int _interval;
    std::vector<std::shared_ptr<IKitchenSpawner>> _spawners;
    std::vector<std::shared_ptr<IKitchenLink>> _kitchens;
};
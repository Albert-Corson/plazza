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
    ~KitchenManager() = default;

    void bindSpawner(std::shared_ptr<IKitchenSpawner> spawner);
    IKitchenLink &queryKitchen();

    void dump()
    {
        std::cout << "Spawners: " << _spawners.size() << std::endl;
        for (auto it = _kitchens.begin(); it != _kitchens.end();) {
            if (!(*it)->isAlive()) {
                it = _kitchens.erase(it);
            } else {
                (*it)->isAvailable();
                ++it;
            }
        }
        std::cout << "Kitchens: " << _kitchens.size() << std::endl;
    }

  private:
    float _multiplier;
    int _cooks;
    int _interval;
    std::vector<std::shared_ptr<IKitchenSpawner>> _spawners;
    std::vector<std::shared_ptr<IKitchenLink>> _kitchens;
};
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
#include "KitchenSpawner/IKitchenLink.hpp"

struct SpawnerInfo {
    SpawnerInfo(std::shared_ptr<IKitchenSpawner> kitchenSpawner)
        : spawner{ kitchenSpawner }
    {
    }

    std::shared_ptr<IKitchenSpawner> spawner;
    unsigned int kitchensCount{ 0 };
};

struct KitchenInfo {
    KitchenInfo(std::shared_ptr<IKitchenLink> kitchenLink, std::shared_ptr<SpawnerInfo> kitchenSpawner)
        : link{ kitchenLink }
        , availableSlots{ kitchenLink->getAvailability() }
        , spawner{ kitchenSpawner }
    {
    }

    std::shared_ptr<IKitchenLink> link;
    unsigned int availableSlots;
    std::weak_ptr<SpawnerInfo> spawner;
};

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

    KitchenManager(float multiplier, int cooks, int interval, const std::vector<Pizza> &pizzaMenu);
    ~KitchenManager();

    void bindSpawner(std::shared_ptr<IKitchenSpawner> spawner);
    void unbindSpawner(std::shared_ptr<IKitchenSpawner> spawner);
    void resetCache();
    IKitchenLink &queryKitchen();
    void dump();

private:
    void clearKitchens();
    int addKitchen(std::shared_ptr<SpawnerInfo> spawner);
    std::vector<KitchenInfo>::iterator removeKitchen(std::vector<KitchenInfo>::iterator it);

    int findBestSpawner() const;
    int findBestKitchen() const;

    float _multiplier;
    int _cooks;
    int _interval;

    std::vector<std::shared_ptr<SpawnerInfo>> _spawners;
    std::vector<KitchenInfo> _kitchens;
    const std::vector<Pizza> &_pizzaMenu;
};
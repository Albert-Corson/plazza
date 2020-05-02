/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenManager
*/

#include "KitchenManager.hpp"

KitchenManager::KitchenManager(float multiplier, int cooks, int interval)
    : _multiplier{ multiplier }
    , _cooks{ cooks }
    , _interval{ interval }
{
}

void KitchenManager::bindSpawner(std::shared_ptr<IKitchenSpawner> spawner)
{
    _spawners.emplace_back(spawner);
}

IKitchenLink &KitchenManager::queryKitchen()
{
    for (auto it = _kitchens.begin(); it != _kitchens.end();) {
        const auto &kitchen = *it;
        if (kitchen->isAvailable()) {
            return (*kitchen);
        } else if (!kitchen->isAlive()) {
            it = _kitchens.erase(it);
        } else {
            ++it;
        }
    }
    if (_spawners.size() == 0)
        throw Exception("No spawner bound to the kitchen manager. Cannot create kitchens.");
    auto kitchen = _spawners[0]->spawn(_multiplier, _cooks, _interval);
    if (kitchen.get() == nullptr)
        throw Exception("Failed to create kitchen.");
    _kitchens.emplace_back(kitchen);
    return (*kitchen);
}
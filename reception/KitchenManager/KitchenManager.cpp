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

KitchenManager::~KitchenManager()
{
    for (auto &kitchen : _kitchens) {
        kitchen.link->stop();
    }
}

void KitchenManager::bindSpawner(std::shared_ptr<IKitchenSpawner> spawner)
{
    _spawners.emplace_back(std::make_shared<SpawnerInfo>(spawner));
}

void KitchenManager::unbindSpawner(std::shared_ptr<IKitchenSpawner> spawner)
{
    for (auto it = _spawners.begin(); it != _spawners.end(); ++it) {
        auto &spawnerInfo = *it;
        if (spawnerInfo->spawner == spawner) {
            _spawners.erase(it);
            break;
        }
    }
}

void KitchenManager::resetCache()
{
    for (auto it = _kitchens.begin(); it != _kitchens.end();) {
        auto &kitchen = *it;
        if (kitchen.link->isAlive() == false) {
            it = this->removeKitchen(it);
        } else {
            kitchen.availableSlots = kitchen.link->getAvailability();
            ++it;
        }
    }
}

int KitchenManager::addKitchen(std::shared_ptr<SpawnerInfo> spawner)
{
    int index = _kitchens.size();
    auto kitchen = spawner->spawner->spawn(_multiplier, _cooks, _interval);
    if (kitchen.get() == nullptr)
        return (-1);
    spawner->kitchensCount++;
    _kitchens.emplace_back(KitchenInfo(kitchen, spawner));
    return (index);
}

std::vector<KitchenInfo>::iterator KitchenManager::removeKitchen(std::vector<KitchenInfo>::iterator it)
{
    auto &kitchen = *it;

    if (kitchen.spawner.expired() == false) {
        kitchen.spawner.lock()->kitchensCount--;
    }
    return (_kitchens.erase(it));
}

void KitchenManager::clearKitchens()
{
    for (auto it = _kitchens.begin(); it != _kitchens.end();) {
        auto &kitchen = *it;
        if (!kitchen.link->isAlive()) {
            it = this->removeKitchen(it);
        } else {
            ++it;
        }
    }
}

int KitchenManager::findBestSpawner() const
{
    if (_spawners.size() == 0)
        return (-1);

    int index = 0;
    int bestIndex = -1;
    unsigned int minKitchens = _spawners[0]->kitchensCount;

    for (const auto &spawnerInfo : _spawners) {
        if (minKitchens >= spawnerInfo->kitchensCount) {
            bestIndex = index;
        }
        ++index;
    }
    return (bestIndex);
}

int KitchenManager::findBestKitchen() const
{
    if (_kitchens.size() == 0)
        return (-1);

    int index = 0;
    int bestIndex = -1;
    unsigned int maxAvailableSlots = _kitchens[0].availableSlots;

    for (const auto &kitchen : _kitchens) {
        if (kitchen.availableSlots >= maxAvailableSlots) {
            maxAvailableSlots = kitchen.availableSlots;
            bestIndex = index;
        }
        ++index;
    }
    return (bestIndex);
}

IKitchenLink &KitchenManager::queryKitchen()
{
    this->clearKitchens();
    int kitchenId = this->findBestKitchen();
    if (kitchenId == -1 || _kitchens[kitchenId].availableSlots == 0) {
        this->resetCache();
        kitchenId = this->findBestKitchen();
    }
    if (kitchenId == -1 || _kitchens[kitchenId].availableSlots == 0) {
        int spawnerId = this->findBestSpawner();
        if (spawnerId == -1)
            throw Exception("No spawner bound to the kitchen manager. Cannot create kitchens.");
        kitchenId = this->addKitchen(_spawners[spawnerId]);
        if (kitchenId == -1)
            throw Exception("Failed to create a new kitchen");
    }
    _kitchens[kitchenId].availableSlots--;
    return (*_kitchens[kitchenId].link);
}
/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#include "Kitchen.hpp"

Kitchen::Cook::Cook(const double &cookingMutliplier, std::shared_ptr<ResourceLock<std::list<Pizza>>> &orderQueue, std::shared_ptr<std::vector<ResourceLock<Ingredient>>> &fridge)
    : _cookingMutliplier(cookingMutliplier)
    , _orderQueue(orderQueue)
    , _fridge(fridge)
    , _thread(nullptr)
    , _isEmployed(true)
    , _currentOrder(nullptr)
{
}

Kitchen::Cook::Cook(Kitchen::Cook &&other)
    : _cookingMutliplier(other._cookingMutliplier)
    , _orderQueue(other._orderQueue)
    , _fridge(other._fridge)
    , _thread(std::move(other._thread))
    , _isEmployed(other._isEmployed)
    , _currentOrder(nullptr)
{
}

void Kitchen::Cook::layOff() noexcept
{
    _isEmployed = false;
    _thread->join();
}

void Kitchen::Cook::getWorking()
{
    _thread = std::make_unique<Thread>([&]() {
        _getWorking();
    });
}


void Kitchen::Cook::_getWorking()
{
    auto queueLock = _orderQueue.lock();

    while (_isEmployed && !_orderQueue.expired() && !_fridge.expired()) {
        queueLock->wait([](const auto &queue) {
            return (queue.size() > 0);
        });
        queueLock->apply([&](auto &queue) {
            _currentOrder = std::make_unique<Pizza>(queue.front());
        });
        queueLock->notify_all();
        _makePizza();
    }
}

void Kitchen::Cook::_makePizza()
{
    auto fridge = _fridge.lock();
    size_t needed = 0;

    if (!fridge)
        throw Exception("internal memory error");
    for (const auto &it : _currentOrder->getIngredients()) {
        needed = it.getAmount();
        auto ingredient = std::find_if(fridge->begin(), fridge->end(), [&](auto &curr) {
            return (curr.read().getName() == it.getName());
        });
        if (ingredient == fridge->end())
            throw Exception("Unknown ingredient in menu");
        ingredient->apply([&needed](auto &elem) {
            needed -= elem.take(needed);
        });
        while (needed != 0) {
            (*ingredient)->waitForRestock();
            ingredient->apply([&needed](auto &elem) {
                elem.restock();
                needed -= elem.take(needed);
            });
        }
    }
    _currentOrder->cook(_cookingMutliplier);
}
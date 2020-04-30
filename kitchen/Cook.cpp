/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#include "Cook.hpp"
#include <unistd.h>

Cook::Cook(std::shared_ptr<OrderQueue> &orderQueue, std::shared_ptr<Fridge> &fridge, float cookTimeMultiplier)
    : _orderQueue(orderQueue)
    , _fridge(fridge)
    , _cookTimeMultiplier(cookTimeMultiplier)
    , _running(false)
    , _cooking(false)
{
}

Cook::Cook(Cook &&other)
    : _worker(std::move(other._worker))
    , _orderQueue(std::move(other._orderQueue))
    , _fridge(std::move(other._fridge))
    , _cookTimeMultiplier(other._cookTimeMultiplier)
    , _running(other._running)
    , _cooking(other._cooking)
{
}

Cook::~Cook()
{
    _running = false;
    _worker.join();
}

bool Cook::isCooking() const noexcept
{
    return (_cooking);
}

void Cook::start()
{
    _running = true;
    _worker.run([&]() {
        while (_running) {
            _cookNext();
        }
    });
}

void Cook::_cookNext()
{
    const Pizza pizza = _orderQueue->waitForOrder();

    _cooking = true;
    for (const auto &it : pizza.getRecipe())
        _fridge->take(it.getName(), it.getAmount());

    usleep(static_cast<float>(pizza.getCookTime()) * _cookTimeMultiplier);

    _cooking = false;
    // TO DO: log pizzas
}

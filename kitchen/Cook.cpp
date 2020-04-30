/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#include <ostream>
#include <thread>
#include <chrono>

#include "Cook.hpp"

Cook::Cook(const std::weak_ptr<OrderQueue> &orderQueue, const std::weak_ptr<Fridge> &fridge, float cookTimeMultiplier, std::ostream &logOut)
    : _logOut(logOut)
    , _orderQueue(orderQueue)
    , _fridge(fridge)
    , _cookTimeMultiplier(cookTimeMultiplier)
    , _running(false)
    , _cooking(false)
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
    auto queuePtr = _orderQueue.lock();
    auto fridgePtr = _fridge.lock();

    if (queuePtr == nullptr || fridgePtr == nullptr) {
        _running = false;
        return;
    }
    try {
        const Pizza pizza = queuePtr->waitForOrder();
        _cooking = true;
        for (const auto &it : pizza.getRecipe())
            fridgePtr->take(it.getName(), it.getAmount());

        float realtime = pizza.getCookTime();
        realtime *= _cookTimeMultiplier;
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<size_t>(realtime)));

        _cooking = false;
        _logOut << pizza.getName() << std::endl;
    } catch (const Exception &) {
        _running = false;
        return;
    }
}

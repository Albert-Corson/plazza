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

Cook::Cook(const std::shared_ptr<OrderQueue> &orderQueue, const std::shared_ptr<Fridge> &fridge, float cookTimeMultiplier, std::shared_ptr<Log> &logOut)
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
    try {
        Pizza &pizza = _orderQueue->waitForOrder();
        _cooking = true;
        for (const auto &it : pizza.getRecipe())
            _fridge->take(it.getName(), it.getAmount());

        float realtime = pizza.getCookTime();
        realtime *= _cookTimeMultiplier;
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<size_t>(realtime)));
        const std::string &end = Clock::getCurrentTime();

        pizza.setStatus(Pizza::COOKED);
        std::string logStr = end + " - " + pizza.getName() + " " + pizzaSizeStr.at(pizza.getSize()) + " (" + std::to_string(static_cast<size_t>(realtime)) + "ms)";
        _logOut->log(logStr);
        _cooking = false;
    } catch (const Exception &) {
        _running = false;
        return;
    }
}

/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Fridge
*/

#include "Fridge.hpp"
#include <unistd.h>

Fridge::Exception::Exception(const std::string &msg)
    : ::Exception("Fridge::Exception: " + msg)
{
}

Fridge::Fridge()
    : _restockRate(0)
    , _running(false)
{
}

Fridge::~Fridge() 
{
    _running = false;
    _restocker.join();
}

void Fridge::newIngredient(const std::string_view &ingredient, size_t amount)
{
    if (knownIngredient(ingredient))
        throw Fridge::Exception("addIngredient: `" + std::string(ingredient) + "` already exists");
    _stock.emplace_back(Ingredient(ingredient, amount));
}

bool Fridge::knownIngredient(const std::string_view &ingredient) const noexcept
{
    for (const auto &it : _stock) {
        if (it->getName() == ingredient)
            return (true);
    }
    return (false);
}

void Fridge::run(millisec_t restockRate)
{
    _restockRate = restockRate;
    if (_restockRate < 0)
        throw Fridge::Exception("run: invalid `restockRate`: " + std::to_string(_restockRate));
    _running = true;
    _timer.reset();
    _restocker.run([&]() {
        while (_running) {
            _waitForRestock();
            _restockOneOfEach();
        }
    });
}

void Fridge::_waitForRestock() noexcept
{
    static millisec_t elapsed =  0;
    millisec_t curr = elapsed + _timer.getElapsedMillisecond();

    while (curr < _restockRate) {
        usleep(_restockRate - curr);
        curr = elapsed +_timer.getElapsedMillisecond();
    }
    _timer.reset();
    elapsed = curr - _restockRate;
}

void Fridge::_restockOneOfEach()
{
    for (auto &it : _stock) {
        it.apply([](Ingredient &curr) {
            curr.add();
        });
        it.notify_all();
    }
}

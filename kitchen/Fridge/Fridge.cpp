/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Fridge
*/

#include <thread>

#include "Fridge.hpp"

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
    stop();
}

void Fridge::start(millisec_t restockRate)
{
    if (_running)
        throw Fridge::Exception("start: already running");
    _restockRate = restockRate;
    if (_restockRate < 0)
        throw Fridge::Exception("start: invalid `restockRate`: " + std::to_string(_restockRate));
    _running = true;
    _timer.reset();
}

bool Fridge::tryRestock() noexcept
{
    static millisec_t leftover = 0;

    if (!_running)
        return (false);
    millisec_t elapsed = leftover + _timer.getElapsedMillisecond();
    size_t amount = 0;

    if (elapsed < _restockRate)
        return (false);
    _timer.reset();
    while (elapsed >= _restockRate) {
        ++amount;
        elapsed -= _restockRate;
    }
    _restockEach(amount);
    leftover = elapsed;
    return (true);
}

void Fridge::newIngredient(const std::string_view &ingredient, size_t amount)
{
    if (isKnownIngredient(ingredient))
        throw Fridge::Exception("addIngredient: `" + std::string(ingredient) + "` already exists");
    _stock.emplace_back(Ingredient(ingredient, amount));
}

bool Fridge::isKnownIngredient(const std::string_view &ingredient) const noexcept
{
    for (const auto &it : _stock) {
        if (it->getName() == ingredient)
            return (true);
    }
    return (false);
}

void Fridge::take(const std::string_view &ingredient, size_t amount)
{
    auto elem = std::find_if(_stock.begin(), _stock.end(), [&ingredient](auto &it) {
        return (it->getName() == ingredient);
    });
    while (_running && amount > 0) {
        auto lock = elem->wait([&](const Ingredient &it) {
            return (!_running || it.getAmount() > 0);
        });
        amount -= (*elem)->take(amount);
    }
    if (!_running)
        throw Fridge::Exception("take: fridge not running");
}

void Fridge::stop()
{
    _running = false;
    for (auto &it : _stock)
        it.notify_all();
}

void Fridge::_restockEach(size_t amount) noexcept
{
    for (auto &it : _stock) {
        it.apply([&amount](Ingredient &curr) {
            curr.add(amount);
        });
        it.notify_one();
    }
}

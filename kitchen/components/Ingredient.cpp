/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Ingredient
*/

#include "Kitchen.hpp"
#include <thread>

Kitchen::Ingredient::Ingredient(const std::string_view &ingredient, const millisec_t &restockRate, const size_t &amount)
    : _name(ingredient)
    , _restockRate(restockRate)
    , _amount(amount)
    , _timer(std::make_unique<Clock>())
    , _elapsed(0)
{
}

Kitchen::Ingredient::Ingredient(const Kitchen::Ingredient &other)
    : _name(other._name)
    , _restockRate(other._restockRate)
    , _amount(other._amount)
    , _timer(std::make_unique<Clock>(*other._timer))
    , _elapsed(other._elapsed)
{
}

Kitchen::Ingredient &Kitchen::Ingredient::operator=(const Kitchen::Ingredient &other)
{
    _name = other._name;
    _restockRate = other._restockRate;
    _amount = other._amount;
    _timer = std::make_unique<Clock>(*other._timer);
    _elapsed = other._elapsed;
    return (*this);
}

const std::string_view &Kitchen::Ingredient::getName() const noexcept
{
    return (_name);
}

const size_t &Kitchen::Ingredient::getAmount() const noexcept
{
    return (_amount);
}

void Kitchen::Ingredient::setAmount(size_t amount) noexcept
{
    _amount = amount;
}

void Kitchen::Ingredient::add() noexcept
{
    ++_amount;
}

void Kitchen::Ingredient::remove() noexcept
{
    --_amount;
}

bool Kitchen::Ingredient::available(const size_t &amount) noexcept
{
    restock();
    return (_amount >= amount);
}

size_t Kitchen::Ingredient::take(const size_t &needed) noexcept
{
    size_t ret = 0;
    if (needed >= _amount) {
        ret = _amount;
        _amount = 0;
        return (ret);
    }
    _amount -= needed;
    return (needed);
}

void Kitchen::Ingredient::restock() noexcept
{

    if (_timer == nullptr)
        return;
    _elapsed =+ _timer->getElapsedMillisecond();
    _timer->reset();
    while (_elapsed <= _restockRate) {
        _elapsed -= _restockRate;
        add();
    }
}

void Kitchen::Ingredient::waitForRestock() const noexcept
{
    long elapsed = _elapsed + _timer->getElapsedMillisecond();

    while (elapsed >= _restockRate) {
        std::this_thread::sleep_for(std::chrono::milliseconds(_restockRate - elapsed));
        elapsed = _elapsed + _timer->getElapsedMillisecond();
    }
}

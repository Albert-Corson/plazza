/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Ingredient
*/

#include "Kitchen.hpp"


Kitchen::Ingredient::Ingredient(const std::string_view &ingredient, size_t amount)
    : name(ingredient)
    , _amount(amount)
{
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

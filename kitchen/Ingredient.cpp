/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Ingredient
*/

#include "Ingredient.hpp"

Ingredient::Exception::Exception(const std::string &msg)
    : ::Exception("Ingredient::Exception: " + msg)
{
}

Ingredient::Ingredient(const std::string_view &ingredient, size_t amount)
    : _name(ingredient)
    , _amount(amount)
{
}

Ingredient::Ingredient(const Ingredient &other)
    : _name(other._name)
    , _amount(other._amount)
{
}

Ingredient &Ingredient::operator=(Ingredient &&other)
{
    _name = std::move(other._name);
    _amount = other._amount;
    return (*this);
}

const std::string &Ingredient::getName() const noexcept
{
    return (_name);
}

size_t Ingredient::getAmount() const noexcept
{
    return (_amount);
}

size_t Ingredient::take(size_t wantedAmount)
{
    size_t taken = wantedAmount > _amount ? _amount : wantedAmount;

    _amount -= taken;
    return (taken);
}

void Ingredient::add(size_t amount) noexcept
{
    _amount += amount;
}
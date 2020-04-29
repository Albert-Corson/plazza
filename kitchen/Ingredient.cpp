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

Ingredient& Ingredient::operator=(Ingredient &&other) 
{
    _name = std::move(other._name);
    _amount = other._amount;
    return (*this);
}


const std::string& Ingredient::getName() const noexcept
{
    return (_name);
}

size_t Ingredient::getAmount() const noexcept
{
    return (_amount);
}

void Ingredient::take(size_t amount) 
{
    if (_amount < amount)
        throw Ingredient::Exception("take: tried taking " + std::to_string(amount) + " " + _name + " but the available amount is " + std::to_string(_amount));
    _amount -= amount;
}

void Ingredient::add(size_t amount) noexcept
{
    _amount += amount;
}
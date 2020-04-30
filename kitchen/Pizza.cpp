/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#include <algorithm>

#include "Pizza.hpp"

Pizza::Pizza(const std::string_view &name, millisec_t cookTime)
    : _name(name.data())
    , _cookTime(cookTime)
{
}

Pizza::Pizza(const Pizza &other)
    : _name(other._name)
    , _cookTime(other._cookTime)
    , _recipe(other._recipe)
{
}

const std::string &Pizza::getName() const noexcept
{
    return (_name);
}

millisec_t Pizza::getCookTime() const noexcept
{
    return (_cookTime);
}

const std::vector<Ingredient> &Pizza::getRecipe() const noexcept
{
    return (_recipe);
}

void Pizza::addIngredientToRecipe(Ingredient &&ingredient)
{
    auto exists = std::find_if(_recipe.begin(), _recipe.end(), [&ingredient](const auto &elem) {
        return (ingredient.getName() == elem.getName());
    });

    if (exists != _recipe.cend()) {
        *exists = std::move(ingredient);
        return;
    }
    _recipe.emplace_back(std::move(ingredient));
}

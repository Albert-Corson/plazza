/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#include <chrono>
#include <thread>

#include "Kitchen.hpp"

Kitchen::Pizza::Pizza(const std::string_view &pizza, const millisec_t &cookTime)
    : _name(pizza)
    , _cookingTime(cookTime)
{
}

Kitchen::Pizza::Pizza(const Pizza &other)
    : _name(other._name)
    , _cookingTime(other._cookingTime)
    , _ingredients(other._ingredients)
{
}

const std::string_view &Kitchen::Pizza::getName() const noexcept
{
    return (_name);
}

const std::vector<Kitchen::Ingredient> &Kitchen::Pizza::getIngredients() const noexcept
{
    return (_ingredients);
}

void Kitchen::Pizza::addIngredient(const std::string_view &ingredientName, const size_t &amount)
{
    for (auto &it : _ingredients) {
        if (it.getName() == ingredientName) {
            it.setAmount(amount);
            return;
        }
    }
    _ingredients.emplace_back(ingredientName, 0, amount);
}

void Kitchen::Pizza::cook(const double &timeMultiplier) const noexcept
{
    double realtime = static_cast<double>(_cookingTime) * timeMultiplier;

    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long>(realtime)));
}

/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#include "Kitchen.hpp"

Kitchen::Pizza::Pizza(const std::string_view &pizza, const std::chrono::milliseconds time)
    : name(pizza)
    , cookingTime(time)
{
}

void Kitchen::Pizza::addIngredient(const std::string_view &ingredientName, const size_t &amount)
{
    for (auto &it : _ingredients) {
        if (it.name == ingredientName) {
            it.setAmount(amount);
            return;
        }
    }
    _ingredients.push_back(Ingredient(ingredientName, amount));
}

size_t Kitchen::Pizza::getRequiredIngredientAmt(const std::string_view &ingredientName) const noexcept
{
    for (const auto &it : _ingredients) {
        if (it.name == ingredientName)
            return (it.getAmount());
    }
    return (0);
}

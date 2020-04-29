/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#pragma once

#include <string_view>

#include "deps/Clock.hpp"
#include "Ingredient.hpp"

class Pizza {
    public:
        Pizza(const std::string_view &name, millisec_t cookTime);

        const std::string &getName() const noexcept;
        millisec_t getCookTime() const noexcept;
        const std::vector<Ingredient> &getRecipe() const noexcept;

        void addIngredientToRecipe(Ingredient &&ingredient);

    private:
        const std::string _name;
        const millisec_t _cookTime;
        std::vector<Ingredient> _recipe;
};

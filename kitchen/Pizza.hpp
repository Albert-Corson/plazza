/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#pragma once

#include <string_view>
#include <vector>

#include "deps/Clock.hpp"
#include "deps/pizzaSize.hpp"
#include "Ingredient.hpp"

class Pizza {
    public:
        enum status_t {
            IDLE = 0,
            COOKING = 1,
            COOKED = 2,
        };

        Pizza(const std::string_view &name, millisec_t cookTime, pizzaSize_t size = pizzaSize_t::UNDEF);
        Pizza(const Pizza &other);

        const std::string &getName() const noexcept;
        millisec_t getCookTime() const noexcept;
        const std::vector<Ingredient> &getRecipe() const noexcept;
        status_t getStatus() const noexcept;
        pizzaSize_t getSize() const noexcept;
        void setStatus(status_t status) noexcept;
        void setSize(pizzaSize_t size) noexcept;
        void addIngredientToRecipe(Ingredient &&ingredient);

    private:
        const std::string _name;
        pizzaSize_t _size;
        const millisec_t _cookTime;
        status_t _status;
        std::vector<Ingredient> _recipe;
};

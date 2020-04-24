/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#pragma once

#include "deps/ResourceLock.hpp"
#include <string_view>
#include <vector>

class Kitchen {
    public:
        class Ingredient;
        class Pizza;
        class Cook;

        Kitchen(const std::chrono::milliseconds cookingMutliplier, const size_t maxCooks, const std::chrono::milliseconds restockDelay);

    private:
        const std::chrono::milliseconds _cookingMutliplier;
        const std::chrono::milliseconds _restockDelay;
        const size_t _maxCooks;

        std::vector<Ingredient> _fridge;
        std::vector<Pizza> _menu;
        std::vector<Cook> _cooks;
};

class Kitchen::Ingredient {
    public:
        const std::string_view name;

        Ingredient(const std::string_view &ingredient, size_t amount = 5);

        const size_t &getAmount() const noexcept;
        void setAmount(size_t amount) noexcept;
        void add() noexcept;
        void remove() noexcept;

    private:
        size_t _amount;
};

class Kitchen::Pizza {
    public:
        const std::string_view name;
        const std::chrono::milliseconds cookingTime;

        Pizza(const std::string_view &pizza, const std::chrono::milliseconds time);

        void addIngredient(const std::string_view &ingredientName, const size_t &amount);
        size_t getRequiredIngredientAmt(const std::string_view &ingredientName) const noexcept;

    private:
        std::vector<Ingredient> _ingredients;
};

class Kitchen::Cook {
    public:
        Cook() = default;
        ~Cook() = default;

    private:
        std::array<Pizza, 2> _orders;
};

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
#include "../Ingredient/Ingredient.hpp"

class Pizza {
    public:
        enum status_t {
            IDLE = 0,
            COOKING = 1,
            COOKED = 2,
        };

        /**
         * @brief Construct a new Pizza object
         * 
         * @param name name of the pizza
         * @param cookTime its cooking time
         * @param size its size, undefined by default
        **/
        Pizza(const std::string_view &name, millisec_t cookTime, pizzaSize_t size = pizzaSize_t::UNDEF);
        Pizza(const Pizza &other);

        /**
         * @brief add an `ingredient` to the recipe of the pizza
        **/
        void addIngredientToRecipe(Ingredient &&ingredient);

        /**
         * @brief Get the name of the pizza
        **/
        const std::string &getName() const noexcept;

        /**
         * @brief Get the cooking time of the pizza in milliseconds
        **/
        millisec_t getCookTime() const noexcept;

        /**
         * @brief Get the ingredients needed to make this pizza
         * 
         * @return const std::vector<Ingredient> &
        **/
        const std::vector<Ingredient> &getRecipe() const noexcept;

        /**
         * @brief Get the status of the pizza
        **/
        status_t getStatus() const noexcept;

        /**
         * @brief Get the size of the pizza
        **/
        pizzaSize_t getSize() const noexcept;

        /**
         * @brief Set status of the pizza
        **/
        void setStatus(status_t status) noexcept;

        /**
         * @brief Set the size of the pizza
        **/
        void setSize(pizzaSize_t size) noexcept;

    private:
        const std::string _name;
        pizzaSize_t _size;
        const millisec_t _cookTime;
        status_t _status;
        std::vector<Ingredient> _recipe;
};

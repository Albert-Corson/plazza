/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#pragma once

#include <string_view>
#include <vector>
#include <algorithm>

#include "deps/Clock.hpp"
#include "deps/plazza/pizzaSize.hpp"
#include "deps/plazza/Ingredient.hpp"

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
        Pizza(const std::string_view &name, millisec_t cookTime, pizzaSize_t size = pizzaSize_t::UNDEF)
            : _name(name.data())
            , _size(size)
            , _cookTime(cookTime)
            , _status(IDLE)
        {
        }
        Pizza(const Pizza &other)
            : _name(other._name)
            , _cookTime(other._cookTime)
            , _status(other._status)
            , _recipe(other._recipe)
        {
        }

        /**
             * @brief add an `ingredient` to the recipe of the pizza
            **/
        void addIngredientToRecipe(Ingredient &&ingredient)
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

        /**
             * @brief Get the name of the pizza
            **/
        const std::string &getName() const noexcept
        {
            return (_name);
        }

        /**
             * @brief Get the cooking time of the pizza in milliseconds
            **/
        millisec_t getCookTime() const noexcept
        {
            return (_cookTime);
        }

        /**
             * @brief Get the ingredients needed to make this pizza
             * 
             * @return const std::vector<Ingredient> &
            **/
        const std::vector<Ingredient> &getRecipe() const noexcept
        {
            return (_recipe);
        }

        /**
             * @brief Get the status of the pizza
            **/
        status_t getStatus() const noexcept
        {
            return (_status);
        }

        /**
             * @brief Get the size of the pizza
            **/
        pizzaSize_t getSize() const noexcept
        {
            return (_size);
        }

        /**
             * @brief Set status of the pizza
            **/
        void setStatus(status_t status) noexcept
        {
            _status = status;
        }

        /**
             * @brief Set the size of the pizza
            **/
        void setSize(pizzaSize_t size) noexcept
        {
            _size = size;
        }

    private:
        const std::string _name;
        pizzaSize_t _size;
        const millisec_t _cookTime;
        status_t _status;
        std::vector<Ingredient> _recipe;
};

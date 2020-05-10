/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Ingredient
*/

#pragma once

#include <string_view>

class Ingredient {
    public:
        Ingredient(const std::string_view &ingredient, size_t amount)
            : _name(ingredient)
            , _amount(amount)
        {
        }
        Ingredient(const Ingredient &other)
            : _name(other._name)
            , _amount(other._amount)
        {
        }
        Ingredient() = default;
        Ingredient &operator=(Ingredient &&other)
        {
            _name = std::move(other._name);
            _amount = other._amount;
            return (*this);
        }

        /**
             * @brief Get the ingredient name
             * 
             * @return const std::string &
            **/
        const std::string &getName() const noexcept
        {
            return (_name);
        }

        /**
             * @brief Get the amount of the ingredient
             * 
             * @return size_t
            **/
        size_t getAmount() const noexcept
        {
            return (_amount);
        }

        /**
             * @brief removed up to `wantedAmount` of ingredient, the removed amount is returned
            **/
        size_t take(size_t wantedAmount)
        {
            size_t taken = wantedAmount > _amount ? _amount : wantedAmount;

            _amount -= taken;
            return (taken);
        }

        /**
             * @brief add `amount` of ingredient
            **/
        void add(size_t amount = 1) noexcept
        {
            _amount += amount;
        }

    private:
        std::string _name;
        size_t _amount;
};

/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Ingredient
*/

#pragma once

#include <string_view>

#include "deps/Exception.hpp"

class Ingredient {
    public:
        class Exception;

        Ingredient(const std::string_view &ingredient, size_t amount);
        Ingredient(const Ingredient &other);
        Ingredient() = default;
        Ingredient &operator=(Ingredient &&other);

        /**
         * @brief Get the ingredient name
         * 
         * @return const std::string &
        **/
        const std::string &getName() const noexcept;

        /**
         * @brief Get the amount of the ingredient
         * 
         * @return size_t
        **/
        size_t getAmount() const noexcept;

        /**
         * @brief removed up to `wantedAmount` of ingredient, the removed amount is returned
        **/
        size_t take(size_t wantedAmount);

        /**
         * @brief add `amount` of ingredient
        **/
        void add(size_t amount = 1) noexcept;

    private:
        std::string _name;
        size_t _amount;
};

class Ingredient::Exception : public ::Exception {
    public:
        Exception(const std::string &msg);
        ~Exception() override = default;
};

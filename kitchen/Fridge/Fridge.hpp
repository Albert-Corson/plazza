/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Fridge
*/

#pragma once

#include <vector>

#include "deps/Clock.hpp"
#include "deps/ResourceLock.hpp"
#include "deps/Thread.hpp"
#include "deps/plazza/Ingredient.hpp"

class Fridge {
    public:
        class Exception;

        Fridge();
        ~Fridge();

        /**
         * @brief starts the restock timer and sets the `restockRate`
         * 
         * @param restockRate restock rate in milliseconds
        **/
        void start(millisec_t restockRate);

        /**
         * @brief tries to restock the fridge if the elapsed time is sufficient
         * resets the timer if successful
         * @return bool success/fail
        **/
        bool tryRestock() noexcept;

        /**
         * @brief adds a new ingredient to the fridge
        **/
        void newIngredient(const std::string_view &ingredient, size_t amount = 5);

        /**
         * @brief checks if `ingredient` is known by the fridge (even if the amount contained is 0)
        **/
        bool isKnownIngredient(const std::string_view &ingredient) const noexcept;

        /**
         * @brief takes `amount` `ingredient`, if not enough is presents if waits for restocks
        **/
        void take(const std::string_view &ingredient, size_t amount);

        /**
         * @brief stops the fridge from running
        **/
        void stop();

    private:
        millisec_t _restockRate;
        Clock _timer;
        bool _running;
        std::vector<ResourceLock<Ingredient>> _stock;

        /**
         * @brief restocks each ingredients by `amount`
        **/
        void _restockEach(size_t amount = 1) noexcept;
};

class Fridge::Exception : public ::Exception {
    public:
        Exception(const std::string &msg);
        ~Exception() override = default;
};
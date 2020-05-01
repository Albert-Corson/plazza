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
#include "Ingredient.hpp"

class Fridge {
    public:
        class Exception;

        Fridge();
        ~Fridge();

        void start(millisec_t restockRate);
        bool tryRestock() noexcept;
        void newIngredient(const std::string_view &ingredient, size_t amount = 5);
        bool isKnownIngredient(const std::string_view &ingredient) const noexcept;
        void take(const std::string_view &ingredient, size_t amount);
        void stop();

    private:
        millisec_t _restockRate;
        Clock _timer;
        bool _running;
        std::vector<ResourceLock<Ingredient>> _stock;

        void _restockOneOfEach() noexcept;
};

class Fridge::Exception : public ::Exception {
    public:
        Exception(const std::string &msg);
        ~Exception() override = default;
};
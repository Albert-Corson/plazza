/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#pragma once

#include <string_view>
#include <vector>
#include <unordered_map>
#include <memory>
#include <list>

#include "deps/ResourceLock.hpp"
#include "deps/Exception.hpp"
#include "deps/Clock.hpp"
#include "deps/Thread.hpp"

typedef long millisec_t;

class Kitchen {
    public:
        class Exception;

        Kitchen(const double &cookingMutliplier, const size_t &cooks, const millisec_t &restockRate);
        ~Kitchen();

        void addPizzaToMenu(const std::string_view &pizza, const millisec_t &cookTime, const std::unordered_map<std::string_view, size_t> &ingredients);
        size_t getAvailQueueSize() const noexcept;
        void takeOrder(const std::string_view &pizzaName);

    private:
        class Ingredient;
        class Pizza;
        class Cook;

        const double _cookingMutliplier;
        const millisec_t _restockRate;
        const size_t _maxOrderQueue;

        std::shared_ptr<std::vector<ResourceLock<Ingredient>>> _fridge;
        std::shared_ptr<ResourceLock<std::list<Pizza>>> _orderQueue;
        std::vector<Pizza> _menu;
        std::vector<Cook> _cooks;
};

class Kitchen::Exception : public ::Exception {
    public:
        Exception(const std::string &msg);
        Exception(std::string &&msg);
        ~Exception() override = default;
};

class Kitchen::Ingredient {
    public:

        Ingredient(const std::string_view &ingredient, const millisec_t &restockRate, const size_t &amount = 5);
        Ingredient() = default;
        Ingredient(const Ingredient &other);
        Ingredient &operator=(const Ingredient &other);

        const std::string_view &getName() const noexcept;
        const size_t &getAmount() const noexcept;
        void setAmount(size_t amount) noexcept;
        void add() noexcept;
        void remove() noexcept;
        bool available(const size_t &amount) noexcept;
        size_t take(const size_t &needed) noexcept;
        void restock() noexcept;
        void waitForRestock() const noexcept;

    private:
        std::string_view _name;
        millisec_t _restockRate;
        size_t _amount;
        std::unique_ptr<Clock> _timer;
        millisec_t _elapsed;

};

class Kitchen::Pizza {
    public:

        Pizza(const std::string_view &pizza, const millisec_t &cookTime);
        Pizza(const Pizza &other);

        const std::string_view &getName() const noexcept;
        const std::vector<Ingredient> &getIngredients() const noexcept;
        void addIngredient(const std::string_view &ingredientName, const size_t &amount);
        void cook(const double &timeMultiplier) const noexcept;

    private:
        std::string_view _name;
        const millisec_t _cookingTime;
        std::vector<Ingredient> _ingredients;
};

class Kitchen::Cook {
    public:
        Cook(const double &cookingMutliplier, std::shared_ptr<ResourceLock<std::list<Pizza>>> &orderQueue, std::shared_ptr<std::vector<ResourceLock<Ingredient>>> &fridge);
        Cook(Cook &&other);
        ~Cook() = default;

        void layOff() noexcept;
        void getWorking();

    private:
        const double _cookingMutliplier;
        std::weak_ptr<ResourceLock<std::list<Pizza>>> _orderQueue;
        std::weak_ptr<std::vector<ResourceLock<Ingredient>>> _fridge;
        std::unique_ptr<Thread> _thread;
        bool _isEmployed;
        std::unique_ptr<Pizza> _currentOrder;

        void _getWorking();
        void _makePizza();
};

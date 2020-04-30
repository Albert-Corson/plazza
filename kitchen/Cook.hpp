/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#pragma once

#include <list>

#include "deps/Thread.hpp"
#include "Pizza.hpp"
#include "Fridge.hpp"
#include "OrderQueue.hpp"

class Cook {
    public:
        Cook(std::shared_ptr<OrderQueue> &orderQueue, std::shared_ptr<Fridge> &fridge, float cookTimeMultiplier);
        Cook(Cook &&other);
        ~Cook();

        bool isCooking() const noexcept;
        void start();

    private:
        Thread _worker;
        std::shared_ptr<OrderQueue> _orderQueue;
        std::shared_ptr<Fridge> _fridge;
        const float _cookTimeMultiplier;
        bool _running;
        bool _cooking;

        void _cookNext();
};

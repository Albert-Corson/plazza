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
        Cook(const std::weak_ptr<OrderQueue> &orderQueue, const std::weak_ptr<Fridge> &fridge, float cookTimeMultiplier, std::ostream &logOut);
        ~Cook();

        bool isCooking() const noexcept;
        void start();

    private:
        Thread _worker;
        std::ostream &_logOut;
        std::weak_ptr<OrderQueue> _orderQueue;
        std::weak_ptr<Fridge> _fridge;
        const float _cookTimeMultiplier;
        bool _running;
        bool _cooking;

        void _cookNext();
};

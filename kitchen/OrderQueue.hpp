/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** OrderQueue
*/

#pragma once

#include <list>

#include "deps/ResourceLock.hpp"
#include "Pizza.hpp"

class OrderQueue {
    public:
        OrderQueue() = default;
        ~OrderQueue() = default;

        const Pizza waitForOrder();
        void addOrder(const Pizza &pizza);

    private:
        ResourceLock<std::list<Pizza>> _queue;
};

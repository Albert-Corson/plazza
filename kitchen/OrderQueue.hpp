/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** OrderQueue
*/

#pragma once

#include <list>

#include "deps/ResourceLock.hpp"
#include "deps/Exception.hpp"
#include "Pizza.hpp"

class OrderQueue {
    public:
        class Exception;

        OrderQueue();
        ~OrderQueue();

        const Pizza waitForOrder();
        void addOrder(const Pizza &pizza);
        size_t getSize() const noexcept;
        void close();

    private:
        bool _running;
        ResourceLock<std::list<Pizza>> _queue;
};

class OrderQueue::Exception : public ::Exception {
    public:
        Exception(const std::string &msg);
        ~Exception() override = default;
};

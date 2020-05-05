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
#include "../Pizza/Pizza.hpp"

class OrderQueue {
    public:
        class Exception;

        OrderQueue();
        ~OrderQueue();

        /**
         * @brief blocks the calling thread and waiting for the order queue have orders to take
         * 
         * @return Pizza & reference to the taken order
         * @throw OrderQueue::Exception if the queue was stopped
        **/
        Pizza &waitForOrder();

        /**
         * @brief add an order to the queue
        **/
        void addOrder(const Pizza &pizza, pizzaSize_t size);

        /**
         * @brief get the size of the queue
        **/
        size_t getSize() const noexcept;

        /**
         * @brief get a read-only reference to the queue
        **/
        const std::list<Pizza> &getQueue() const noexcept;

        /**
         * @brief removed cooked pizza from the queue
        **/
        void removeCookedPizzas();

        /**
         * @brief stop the queue
        **/
        void close();

        /**
         * @brief waits for the queue to be available and locks it for modifications
        **/
        void lock();

        /**
         * @brief unlocks the queue
        **/
        void unlock();

    private:
        bool _running;
        ResourceLock<std::list<Pizza>> _queue;
};

class OrderQueue::Exception : public ::Exception {
    public:
        Exception(const std::string &msg);
        ~Exception() override = default;
};

/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#pragma once

#include <list>

#include "deps/Thread.hpp"
#include "../Pizza/Pizza.hpp"
#include "../Fridge/Fridge.hpp"
#include "../OrderQueue/OrderQueue.hpp"
#include "../Log/Log.hpp"

class Cook {
    public:
        /**
         * @brief Construct a new Cook object
         * 
         * @param orderQueue a poiter to the order queue to get orders from
         * @param fridge a pointer to the fridge from which to take ingredients
         * @param cookTimeMultiplier cooking time multiplier
         * @param logOut a stream to log done pizzas onto
        **/
        Cook(const std::shared_ptr<OrderQueue> &orderQueue, const std::shared_ptr<Fridge> &fridge, float cookTimeMultiplier, std::shared_ptr<Log> &logOut);
        ~Cook();

        /**
         * @brief returns the state of the cook: cooking (true) / not cooking(false)
         * 
         * @return bool
        **/
        bool isCooking() const noexcept;

        /**
         * @brief starts the threaded cook
         * waits for pizzas to be added to the order queue and cooks them
        **/
        void start();

    private:
        Thread _worker;
        std::shared_ptr<Log> _logOut;
        std::shared_ptr<OrderQueue> _orderQueue;
        std::shared_ptr<Fridge> _fridge;
        const float _cookTimeMultiplier;
        bool _running;
        bool _cooking;

        /**
         * @brief cooks the next available pizza on the order queue
        **/
        void _cookNext();
};

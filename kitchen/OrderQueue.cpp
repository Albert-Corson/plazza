/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** OrderQueue
*/

#include "OrderQueue.hpp"

const Pizza OrderQueue::waitForOrder()
{
    auto lockGuard = _queue.wait([](const auto &queue) {
        return (queue.size() > 0);
    });
    Pizza pizza(_queue->front());
    _queue->pop_front();
    return (pizza);
}

void OrderQueue::addOrder(const Pizza &pizza)
{
    _queue.apply([&pizza](auto &queue) {
        queue.emplace_back(pizza);
    });
    _queue.notify_all();
}

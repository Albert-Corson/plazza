/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** OrderQueue
*/

#include "OrderQueue.hpp"

OrderQueue::Exception::Exception(const std::string &msg)
    : ::Exception("OrderQueue::Exception: " + msg)
{
}

OrderQueue::OrderQueue()
    : _running(true)
{
}

OrderQueue::~OrderQueue()
{
    close();
}

const Pizza OrderQueue::waitForOrder()
{
    auto lockGuard = _queue.wait([&](const auto &queue) {
        return (queue.size() > 0 || !_running);
    });
    if (!_running)
        throw OrderQueue::Exception("waitForOrder: queue closed");
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

size_t OrderQueue::getSize() const noexcept
{
    return (_queue.read().size());
}

void OrderQueue::close() 
{
    _running = false;
    _queue.notify_all();
}

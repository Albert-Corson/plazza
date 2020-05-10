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

Pizza &OrderQueue::waitForOrder()
{
    auto lockGuard = _queue.wait([&](const auto &queue) {
        if (!_running)
            return (true);
        for (const auto &it : queue) {
            if (it.getStatus() == Pizza::ST_IDLE)
                return (true);
        }
        return (false);
    });
    if (_running) {
        for (auto &it : *_queue) {
            if (it.getStatus() == Pizza::ST_IDLE) {
                it.setStatus(Pizza::ST_AWAIT_RESTOCK);
                return (it);
            }
        }
    }
    throw OrderQueue::Exception("waitForOrder: queue closed");
}

void OrderQueue::addOrder(const Pizza &pizza, Pizza::psize size)
{
    _queue.apply([&pizza, &size](auto &queue) {
        queue.push_back(pizza);
        queue.back().setSize(size);
    });
    _queue.notify_one();
}

size_t OrderQueue::getSize() const noexcept
{
    return (_queue.read().size());
}

const std::list<Pizza>& OrderQueue::getQueue() const noexcept
{
    return (_queue.read());
}

void OrderQueue::removeCookedPizzas() 
{
    auto lock = _queue.unique_lock();
    auto it = _queue->begin();

    while (it != _queue->end()) {
        if (it->getStatus() == Pizza::ST_COOKED) {
            it = _queue->erase(it);
        } else {
            ++it;
        }
    }
}

void OrderQueue::close() 
{
    _running = false;
    _queue.notify_all();
}

void OrderQueue::lock() 
{
    _queue.lock();
}

void OrderQueue::unlock() 
{
    _queue.unique_lock();
}

/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ResourceLock
*/

#pragma once

#include <mutex>
#include <functional>
#include <condition_variable>

#include "Exception.hpp"

template <typename T>
class ResourceLock : private std::recursive_mutex {
    public:
        ResourceLock(const T &data)
            : _resource(std::move(data))
        {
        }
        ResourceLock()
            : ResourceLock(T())
        {
        }
        ~ResourceLock() = default;
        ResourceLock(ResourceLock<T> &&other)
        {
            *this = std::move(other);
        }
        ResourceLock<T> &operator=(ResourceLock<T> &&other)
        {
            _resource = std::move(other._resource);
            return (*this);
        }

        ResourceLock(ResourceLock<T> &other) = delete;
        ResourceLock<T> &operator=(const ResourceLock<T> &other) = delete;

        T *operator->()
        {
            return (&_resource);
        }

        const T *operator->() const
        {
            return (&_resource);
        }

        T &operator*()
        {
            return (_resource);
        }

        const T &operator*() const
        {
            return (_resource);
        }

        using std::recursive_mutex::unlock;

        const T &read() const
        {
            return (_resource);
        }

        T &lock()
        {
            std::recursive_mutex::lock();
            return (_resource);
        }

        T *try_lock()
        {
            if (!std::recursive_mutex::try_lock())
                return (nullptr);
            return (&_resource);
        }

        void apply(std::function<void (T &)> function)
        {
            auto lg = lock_guard();

            function(_resource);
        }

        void try_apply(std::function<void (T &, bool)> function)
        {
            function(_resource, std::recursive_mutex::try_lock());
            unlock();
        }

        std::lock_guard<ResourceLock> lock_guard()
        {
            return (std::lock_guard<ResourceLock>(*this));
        }

        void wait(std::function<bool (const T &)> predicate)
        {
            std::unique_lock<ResourceLock<T>> _unqLock(*this);

            _condVar.wait(_unqLock, [&]() {
                return predicate(_resource);
            });
            _unqLock.unlock();
        }

        void wait()
        {
            std::unique_lock<ResourceLock<T>> unqLock(*this);

            _condVar.wait(unqLock);
            unqLock.unlock();
        }

        void notify_one()
        {
            _condVar.notify_one();
        }

        void notify_all()
        {
            _condVar.notify_all();
        }

    private:
        T _resource;
        std::condition_variable_any _condVar;
};

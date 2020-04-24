/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ResourceLock
*/

#pragma once

#include "Exception.hpp"
#include <mutex>
#include <functional>

template <typename T>
class ResourceLock : private std::recursive_mutex {
    public:
        class Exception : public ::Exception {
            public:
                Exception(const std::string &msg)
                    : ::Exception("ResourceLock<T>::Exception: " + msg)
                {
                }
                ~Exception() override = default;
        };

        ResourceLock(T &&data)
            : _resource(data)
        {
        }
        ResourceLock(T &data)
            : _resource(std::move(data))
        {
        }
        ~ResourceLock() = default;
        ResourceLock(const ResourceLock<T> &other) = delete;
        ResourceLock<T> &operator=(const ResourceLock<T> &other) = delete;

        T *operator->()
        {
            return (&_resource);
        }

        T &operator*()
        {
            return (_resource);
        }

        using std::recursive_mutex::unlock;

        const T &read()
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

    private:
        T _resource;
};

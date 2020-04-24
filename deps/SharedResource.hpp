/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** SharedResource
*/

#pragma once

#include "Exception.hpp"
#include <mutex>
#include <functional>

template <typename T>
class SharedResource : private std::recursive_mutex {
    public:
        class Exception : public ::Exception {
            public:
                Exception(const std::string &msg)
                    : ::Exception("SharedResource<T>::Exception: " + msg)
                {
                }
                ~Exception() override = default;
        };

        SharedResource(T data)
            : _resource(std::move(data))
        {
        }
        ~SharedResource() = default;
        SharedResource(const SharedResource<T> &other) = delete;
        SharedResource<T> &operator=(const SharedResource<T> &other) = delete;

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
            if (std::recursive_mutex::try_lock())
                return (&_resource);
            return (nullptr);
        }
        void apply(std::function<void (T &)> function)
        {
            std::recursive_mutex::lock();
            function(_resource);
            unlock();
        }
        void try_apply(std::function<void (T &)> function)
        {
            if (!std::recursive_mutex::try_lock())
                throw Exception("try_apply: resource is in use");
            function(_resource);
            unlock();
        }

    private:
        T _resource;
};

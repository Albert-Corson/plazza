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
        /**
         * @brief Construct a new ResourceLock object and stores a T variable
         * 
         * @param data the variable to store
        **/
        ResourceLock(const T &data)
            : _resource(std::move(data))
        {
        }
        ResourceLock() = default;
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

        /**
         * @brief access the object stored
         * 
         * @return T *
        **/
        T *operator->()
        {
            return (&_resource);
        }

        /**
         * @brief access the object stored as a const
         * 
         * @return T *
        **/
        const T *operator->() const
        {
            return (&_resource);
        }

        /**
         * @brief access the object stored
         * 
         * @return T *
        **/
        T &operator*()
        {
            return (_resource);
        }

        /**
         * @brief access the object stored as a const
         * 
         * @return T *
        **/
        const T &operator*() const
        {
            return (_resource);
        }

        using std::recursive_mutex::unlock;

        /**
         * @brief returns a read-only reference to the stored variable
         * 
         * @return const T &
        **/
        const T &read() const
        {
            return (_resource);
        }

        /**
         * @brief Locks the mutex assossiated to the stored variable
         * 
         * @return T &
        **/
        T &lock()
        {
            std::recursive_mutex::lock();
            return (_resource);
        }

        /**
         * @brief Tries to lock the mutex assossiated to the stored variable
         * 
         * @return T * if it fails, a nullptr is returned
        **/
        T *try_lock()
        {
            if (!std::recursive_mutex::try_lock())
                return (nullptr);
            return (&_resource);
        }

        /**
         * @brief locks the mutex before applaying `function` onto the stored variable
        **/
        void apply(std::function<void (T &)> function)
        {
            auto lock = unique_lock();

            function(_resource);
        }

        /**
         * @brief tries to lock the mutex before applaying `function` onto the stored variable
         * if locking isn't successful, false is passed as second parameter to `function`, true otherwise
        **/
        void try_apply(std::function<void (T &, bool)> function)
        {
            function(_resource, std::recursive_mutex::try_lock());
            unlock();
        }

        /**
         * @brief returns a newly created unique_lock of the assossiated mutex
        **/
        std::unique_lock<ResourceLock> unique_lock()
        {
            return (std::unique_lock<ResourceLock>(*this));
        }

        /**
         * @brief waits for the stored variable to be modified
         * loops while `predicate` returns false
         * this call is unlocked by a call to notify_one or notify_all
         * 
         * @param predicate
         * @return std::unique_lock<ResourceLock<T>>
        **/
        std::unique_lock<ResourceLock<T>> wait(std::function<bool (const T &)> predicate)
        {
            auto unqLock = unique_lock();

            _condVar.wait(unqLock, [&]() {
                return predicate(_resource);
            });
            return (unqLock);
        }

        /**
         * @brief waits for the stored variable to be modified
         * this call is unlocked by a call to notify_one or notify_all
         * 
         * @return std::unique_lock<ResourceLock<T>> 
        **/
        std::unique_lock<ResourceLock<T>> wait()
        {
            std::unique_lock<ResourceLock<T>> unqLock(*this);

            _condVar.wait(unqLock);
            return (unqLock);
        }

        /**
         * @brief notifies one waiting thread to unlock their call to `wait`
        **/
        void notify_one()
        {
            _condVar.notify_one();
        }

        /**
         * @brief notifies all waiting threads to unlock their call to `wait`
        **/
        void notify_all()
        {
            _condVar.notify_all();
        }

    private:
        T _resource;
        std::condition_variable_any _condVar;
};

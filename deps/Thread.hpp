/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Thread
*/

#pragma once

#include "Exception.hpp"
#include <pthread.h>
#include <string.h>
#include <tuple>

template <typename _FakeLambda>
void *_callFakeLambda(void *target)
{
    _FakeLambda *lambda = reinterpret_cast<_FakeLambda *>(target);

    lambda->call();
    delete lambda;
    return (nullptr);
}

class Thread {
    private:
        template <typename _Function, typename ..._Args>
        class FakeLambda {
            public:
                FakeLambda(bool &running, _Function &&task, _Args &&...args)
                    : _running(running)
                    , _task(std::forward<_Function>(task))
                    , _args { std::forward<_Args>(args)... }
                {
                }

                void operator()()
                {
                    apply(std::make_index_sequence<sizeof...(_Args)> {});
                }

                void call()
                {
                    apply(std::make_index_sequence<sizeof...(_Args)> {});
                    _running = false;
                }

            private:
                bool &_running;
                _Function _task;
                std::tuple<std::decay_t<_Args>...> _args;

                template <size_t ...Idx>
                void apply(std::index_sequence<Idx...>)
                {
                    _task(std::forward<_Args>(std::get<Idx>(_args))...);
                    _running = false;
                }
        };

        pthread_t _id;
        bool _joinable;
        bool _running;

    public:
        class Exception : public ::Exception {
            public:
                Exception(const std::string &msg)
                    : ::Exception("Thread::Exception: " + msg)
                {
                }
                Exception(std::string &&msg)
                    : ::Exception("Thread::Exception: " + msg)
                {
                }
                ~Exception() override = default;
        };

        Thread(const Thread &other) = delete;
        Thread &operator=(const Thread &other) = delete;

        Thread()
            : _id(0)
            , _joinable(false)
            , _running(false)
        {
        }

        /**
         * @brief Construct a new Thread object
         * Starts a new thread and calls `task`
         * 
         * @param task the threaded task to execute
         * @param args the arguments to pass to `task`
        **/
        template <typename Function, typename ...Args>
        explicit Thread(Function &&task, Args &&...args)
        {
            run(std::forward<Function>(task), std::forward<Args>(args)...);
        }

        Thread(Thread &&other)
        {
            *this = std::move(other);
        }

        Thread &operator=(Thread &&other)
        {
            if (_joinable)
                throw Exception("Trying to drop not joined / not detached thread");
            _id = other._id;
            _joinable = other._joinable;
            return (*this);
        }

        /**
         * @brief Destroy the Thread object, throws a Thread::Exception is the thread is still joinable
        **/
        ~Thread() noexcept(false)
        {
            if (_joinable)
                throw Exception("Thread left unjoined / attached");
        }

        /**
         * @brief Runs a task if none is running
         * 
         * @param task the threaded task to execute
         * @param args the arguments to pass to `task`
        **/
        template <typename Function, typename ...Args>
        void run(Function &&task, Args &&...args)
        {
            auto _task = new FakeLambda<Function, Args...>(_running, std::forward<Function>(task), std::forward<Args>(args)...);
            using lambdaType_t = std::remove_reference_t<decltype(*_task)>;

            _joinable = true;
            _running = true;
            int errc = pthread_create(&_id, NULL, &_callFakeLambda<lambdaType_t>, _task);

            if (errc != 0)
                throw Exception(strerror(errc));
        }

        /**
         * @brief Get this thread's ID
         * 
         * @return pthread_t
        **/
        pthread_t get_id()
        {
            return (_id);
        }

        /**
         * @brief tells if the thread is joinable or not
        **/
        bool joinable()
        {
            return (_joinable);
        }

        /**
         * @brief tells if the threaded task is still running
        **/
        bool is_active()
        {
            return (_running);
        }

        /**
         * @brief waits for the end of the thread (and its task)
        **/
        void join()
        {
            int errc = 0;

            if (!_joinable)
                return;
            errc = pthread_join(_id, NULL);
            if (errc != 0)
                throw Exception(strerror(errc));
            _joinable = false;
        }

        /**
         * @brief lets the thread run freely
        **/
        void detach()
        {
            if (!_joinable)
                throw Exception("No thread to detach");
            pthread_detach(_id);
            _joinable = false;
        }
};

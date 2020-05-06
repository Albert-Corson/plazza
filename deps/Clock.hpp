/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Clock
*/

#pragma once

#include <chrono>

typedef long millisec_t;

class Clock {
    public:
        Clock()
            : _start(std::chrono::steady_clock::now())
        {
        }
        Clock(const Clock &other)
            : _start(other._start)
        {
        }
        ~Clock() = default;

        /**
         * @brief Reset the internal time reference
        **/
        void reset()
        {
            _start = std::chrono::steady_clock::now();
        }

        /**
         * @brief Get the elapsed time in milliseconds between the current time and the internal reference
         * 
         * @return millisec_t (a.k.a. long int)
        **/
        millisec_t getElapsedMillisecond() const
        {
            const auto &end = std::chrono::steady_clock::now();
            return (std::chrono::duration_cast<std::chrono::milliseconds>(end - _start).count());
        }

        static std::string getCurrentTime() noexcept
        {
            auto timePoint = std::chrono::system_clock::now();
            std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
            std::string humanTime = std::ctime(&time);

            humanTime = humanTime.substr(0, humanTime.size() - 1);
            return (humanTime);
        }

    private:
        std::chrono::_V2::steady_clock::time_point _start;
};

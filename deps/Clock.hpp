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

        void reset()
        {
            _start = std::chrono::steady_clock::now();
        }

        millisec_t getElapsedMillisecond() const
        {
            const auto &end = std::chrono::steady_clock::now();
            return (std::chrono::duration_cast<std::chrono::milliseconds>(end - _start).count());
        }

    private:
        std::chrono::_V2::steady_clock::time_point _start;
};

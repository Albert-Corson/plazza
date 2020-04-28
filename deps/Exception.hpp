/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Exception
*/

#pragma once

#include <exception>
#include <string>

class Exception : public std::exception {
    public:
        Exception(const std::string &msg)
            : _msg(msg)
        {
        }
        Exception(std::string &&msg)
            : _msg(std::move(msg))
        {
        }
        virtual ~Exception() = default;

        virtual const char *what() const noexcept override
        {
            return (_msg.c_str());
        }

    protected:
        const std::string _msg;
};

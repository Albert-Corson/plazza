/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Exception
*/

#include "Kitchen.hpp"

Kitchen::Exception::Exception(const std::string &msg)
    : ::Exception("Kitchen::Exception: " + msg)
{
}
Kitchen::Exception::Exception(std::string &&msg)
    : ::Exception(std::move("Kitchen::Exception: " + msg))
{
}

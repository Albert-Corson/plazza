/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Log
*/

#include "Log.hpp"
#include <iostream>

void Log::open(const std::string_view &file)
{
    if (_stream->is_open())
        _stream->close();
    _stream->open(file.data());
}

void Log::log(const std::string_view &buffer)
{
    auto lg = _stream.unique_lock();
    if (_stream->good())
        *_stream << buffer << std::endl;
    else
        std::cout << buffer << std::endl;
}

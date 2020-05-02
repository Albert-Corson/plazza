/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Log
*/

#pragma once

#include <fstream>

#include "deps/ResourceLock.hpp"

class Log {
    public:
        void open(const std::string_view &file);
        void log(const std::string_view &buffer);
    private:
        ResourceLock<std::ofstream> _stream;
};

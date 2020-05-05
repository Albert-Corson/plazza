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
        /**
         * @brief open a log file
        **/
        void open(const std::string_view &file);

        /**
         * @brief waits for the file to be available then log the buffer to it with a trailing new-line
        **/
        void log(const std::string_view &buffer);
    private:
        ResourceLock<std::ofstream> _stream;
};

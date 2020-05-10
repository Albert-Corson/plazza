/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** OLogStream
*/

#pragma once

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

#include "deps/ResourceLock.hpp"
#include "deps/Clock.hpp"

class OLogStream {
    public:
        OLogStream()
        {
            *_fdLock = 1;
        }

        /**
         * @brief Construct a new OLogStream object and tries to open `path` for output, if it fails stdout is used
        **/
        OLogStream(const std::string_view &path)
        {
            open(path);
        }

        /**
         * @brief tries to create the file designated by `path` and truncates it if it exists
         * 
         * @return bool success/error
        **/
        static bool makeFile(const std::string_view &path)
        {
            int fd = ::open(path.data(), O_CREAT | O_WRONLY, 0666);

            if (fd < 0)
                return (false);
            close(fd);
            return (true);
        }

        /**
         * @brief open a log file, if it fails, stdout will be used
        **/
        void open(const std::string_view &path)
        {
            *_fdLock = ::open(path.data(), O_WRONLY);
            if (*_fdLock < 0)
                *_fdLock = 1;
        }

        /**
         * @brief waits for the file to be available then log the buffer to it with a trailing new-line
        **/
        void log(const std::string &buffer)
        {
            _fdLock.apply([&buffer](auto &fd) {
                lseek(fd, 0, SEEK_END);
                std::string _buffer = Clock::getCurrentTime() + " - " + buffer + "\n";
                write(fd, _buffer.c_str(), _buffer.size());
            });
        }

    private:
        ResourceLock<int> _fdLock;
};

/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IPC
*/

#pragma once

#include <string_view>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fstream>

// Inter-process communication through named pipes
class IPC {
    public:
        // prepare inter-process communication
        IPC(const std::string_view &path)
            : _path(path)
        {}
        // copy pipe
        IPC(const IPC &other)
            : _path(other._path)
        {}
        ~IPC() = default;

        // copy pipe
        IPC &operator=(const IPC &other)
        {
            this->_path = other._path;
            return (*this);
        }
        // read from fifo
        IPC &read(char *buffer, std::streamsize size)
        {
            std::ifstream in(_path.data(), std::ios::binary);

            in.read(buffer, size);
            return (*this);
        }
        // read from fifo
        IPC &write(const char *buffer, std::streamsize size)
        {
            std::ofstream out(_path.data(), std::ios::binary);

            out.write(buffer, size);
            return (*this);
        }

        // create a FIFO file
        bool make(void)
        {
            return (mkfifo(_path.data(), 0666) == 0);
        }
        // delete a FIFO file
        bool remove(void)
        {
            return (::remove(_path.data()) == 0);
        }

    private:
        std::string_view _path;
};
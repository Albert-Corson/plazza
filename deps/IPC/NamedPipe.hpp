/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** NamedPipe
*/

#pragma once

#include <string_view>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include "deps/IPC/IIPC.hpp"

// Inter-process communication through named pipes
class NamedPipe : public IIPC
{
  public:
    NamedPipe()
        : _path{ nullptr }
    {
    }
    // prepare inter-process communication
    NamedPipe(const std::string_view &path)
        : _path{ path }
    {
    }
    // copy pipe
    NamedPipe(const NamedPipe &other)
        : _path{ other._path }
    {
    }
    ~NamedPipe() = default;

    // copy pipe
    NamedPipe &operator=(const NamedPipe &other)
    {
        this->_path = other._path;
        return (*this);
    }

    // read message from fifo
    void receive(char *buffer, std::streamsize size) const override final
    {
        if (_path == nullptr)
            return;
        std::ifstream in(_path.data(), std::ios::binary);
        in.read(buffer, size);
    }
    // read next line from fifo
    void getline(char *buffer, std::streamsize size) const override final
    {
        if (_path == nullptr)
            return;
        std::ifstream in(_path.data(), std::ios::binary);
        in.getline(buffer, size);
    }
    // write message to fifo
    void send(const char *buffer, std::streamsize size) const override final
    {
        if (_path == nullptr)
            return;
        std::ofstream out(_path.data(), std::ios::binary);
        out.write(buffer, size);
    }
    bool good() const override final
    {
        return (_path != nullptr && access(_path.data(), F_OK | R_OK | W_OK) != -1);
    }

    // set the FIFO path and check for r/w access
    bool open(const std::string_view &path)
    {
        _path = path;
        return (this->good());
    }
    // create a FIFO file
    bool make(void) const
    {
        return (mkfifo(_path.data(), 0666) == 0);
    }
    // delete a FIFO file
    bool remove(void) const
    {
        return (::remove(_path.data()) == 0);
    }

  private:
    std::string_view _path;
};
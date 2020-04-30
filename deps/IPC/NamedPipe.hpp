/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** NamedPipe
*/

#pragma once

#include <string>
#include <memory>
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
    NamedPipe(const std::string &path)
        : _path{ std::make_unique<std::string>(path) }
    {
    }
    // copy pipe
    NamedPipe(const NamedPipe &other)
        : _path{ std::make_unique<std::string>(*other._path) }
    {
    }
    ~NamedPipe() = default;

    // copy pipe
    NamedPipe &operator=(const NamedPipe &other)
    {
        this->_path = std::make_unique<std::string>(*other._path);
        return (*this);
    }

    // read message from fifo
    void receive(char *buffer, std::streamsize size) const override final
    {
        if (_path == nullptr)
            return;
        std::ifstream in(_path->c_str(), std::ios::binary);
        in.read(buffer, size);
    }
    // read next line from fifo
    bool getline(std::string &buffer) const override final
    {
        if (_path == nullptr)
            return (false);
        std::ifstream in(_path->c_str(), std::ios::binary);
        if (!std::getline(in, buffer))
            return (false);
        return (true);
    }
    // write message to fifo
    void send(const char *buffer, std::streamsize size) const override final
    {
        if (_path == nullptr)
            return;
        std::ofstream out(_path->c_str(), std::ios::binary);
        out.write(buffer, size);
    }
    bool good() const override final
    {
        return (_path != nullptr && access(_path->c_str(), F_OK | R_OK | W_OK) != -1);
    }

    // set the FIFO path and check for r/w access
    bool open(const std::string &path)
    {
        _path = std::make_unique<std::string>(path);
        return (this->good());
    }
    // create a FIFO file
    bool make(void) const
    {
        return (mkfifo(_path->c_str(), 0666) == 0);
    }
    // delete a FIFO file
    bool remove(void) const
    {
        return (::remove(_path->c_str()) == 0);
    }

  private:
    std::unique_ptr<std::string> _path;
};
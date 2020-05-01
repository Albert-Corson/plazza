/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IOStream
*/

#pragma once

#include <iostream>
#include "deps/IPC/IIPC.hpp"

// Inter-process communication through standard I/O streams
class IOStream : public IIPC
{
  public:
    IOStream(){};
    IOStream(const IOStream &other){};
    ~IOStream(){};

    IOStream &operator=(const IOStream &other)
    {
        return (*this);
    }

    // read message from std::cin
    void receive(char *buffer, std::streamsize size) override final
    {
        std::cin.read(buffer, size);
    }
    // read next line from std::cin
    bool getline(std::string &buffer) override final
    {
        if (!std::getline(std::cin, buffer))
            return (false);
        return (true);
    }
    // write message to std::cout
    void send(const char *buffer, std::streamsize size) override final
    {
        std::cout.write(buffer, size);
    }
    bool good() const override final
    {
        return (std::cin.good() && std::cout.good());
    }
};
/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Network
*/

#pragma once

#include "IIPC.hpp"
#include "deps/Socket.hpp"

// Inter-process communication through sockets
class Network : public IIPC
{
public:
    Network(){};
    Network(Socket &&socket)
        : _socket(std::move(socket))
    {
    }
    Network(const Network &other){};
    ~Network(){};

    Network &operator=(const Network &other)
    {
        return (*this);
    }

    // read message from std::cin
    void receive(char *buffer, std::streamsize size) override final
    {
        _socket.read(buffer, size);
    }
    // read next line from std::cin
    bool getline(std::string &buffer) override final
    {
        if (!_socket.getline(buffer))
            return (false);
        return (true);
    }
    // write message to std::cout
    void send(const char *buffer, std::streamsize size) override final
    {
        _socket.write(buffer, size);
    }
    bool good() const override final
    {
        return (_socket.good() && _socket.good());
    }

    Socket &getSocket()
    {
        return (_socket);
    }

private:
    Socket _socket;
};
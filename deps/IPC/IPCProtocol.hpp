/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IPCProtocol
*/

#pragma once

#include <string_view>
#include <string>
#include <memory>
#include <vector>
#include "deps/IPC/NamedPipe.hpp"
#include "deps/IPC/IOStream.hpp"
#include "deps/utils/StringUtils.hpp"

// Inter-Process Communication Protocol
class IPCProtocol
{
public:
    IPCProtocol()
        : _comm{ std::make_shared<IOStream>() }
    {
    }
    IPCProtocol(const std::shared_ptr<IIPC> &ipc)
        : _comm{ ipc }
    {
    }
    IPCProtocol(const IPCProtocol &other)
        : _comm{ other._comm }
    {
    }
    ~IPCProtocol() = default;

    IPCProtocol &operator=(const IPCProtocol &other)
    {
        _comm = other._comm;
        return (*this);
    }

    int connect(const std::shared_ptr<IIPC> &ipc)
    {
        _comm = ipc;
        return (this->good());
    }

    void close()
    {
        _comm.reset();
    }

    bool receive(std::vector<std::string> &buffer) const
    {
        std::string strbuffer;

        if (!_comm->getline(strbuffer))
            return (false);
        return (StringUtils::strtab(strbuffer, buffer));
    }

    template<typename... Args>
    void send(const std::string_view &command, Args &&... args) const
    {
        std::ostringstream stream;

        stream << command;
        (void)(int[]){ 0, (stream << " " << args, 0)... };
        stream << "\n";
        _comm->send(stream.str().c_str(), static_cast<std::streamsize>(stream.str().length()));
    }

    bool good() const
    {
        return (_comm.get() != nullptr && _comm->good());
    }

private:
    std::shared_ptr<IIPC> _comm;
};

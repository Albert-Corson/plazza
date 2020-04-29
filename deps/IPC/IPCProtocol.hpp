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
#include <regex>
#include "deps/IPC/NamedPipe.hpp"
#include "deps/IPC/IOStream.hpp"

// Inter-Process Communication Protocol
class IPCProtocol
{
  public:
    IPCProtocol()
        : _comm{ std::make_shared<IOStream>() }
    {
    }
    ~IPCProtocol()
    {
    }

    int connect(const std::shared_ptr<IIPC> &ipc)
    {
        _comm = ipc;
        return (this->good());
    }

    bool receive(std::vector<std::string> &buffer) const
    {
        std::string strbuffer;
        std::regex splitter("(\"[^\"]+\"|[^\\s\"]+)");

        buffer.clear();
        if (!_comm->getline(strbuffer))
            return (false);
        auto it = std::sregex_iterator(strbuffer.begin(), strbuffer.end(), splitter);
        auto end = std::sregex_iterator();
        for (; it != end; ++it) {
            buffer.emplace_back(std::move(it->str()));
        }
        return (true);
    }

    template<typename... Args>
    void send(const std::string_view &command, Args &&... args) const
    {
        std::ostringstream stream;

        stream << command;
        (void)(int[]){ 0, (stream << " " << args, 0)... };
        stream << '\n';
        _comm->send(stream.str().c_str(), static_cast<std::streamsize>(stream.str().length()));
    }

    bool good() const
    {
        return (_comm.get() != nullptr && _comm->good());
    }

  private:
    std::shared_ptr<IIPC> _comm;
};

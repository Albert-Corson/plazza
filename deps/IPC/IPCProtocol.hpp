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
#include <unordered_map>
#include <vector>
#include <regex>
#include "deps/IPC/NamedPipe.hpp"
#include "deps/IPC/IOStream.hpp"

using commandInfo = struct commandInfo {
    std::size_t minArgc;
    std::size_t maxArgc;
    std::string usage;
};

const std::unordered_map<std::string_view, commandInfo> commandsList = {
    { "INIT", { 4, 4, "INIT <multiplier> <cooks> <refill>: Initialize a kitchen." } },
    { "LEARN", { 4, 0, "LEARN <name> <time> <ingredient>...: Learn a pizza recipe." } },
    { "COOK", { 2, 2, "COOK <name>: Start cooking a pizza." } },
    { "STOP", { 1, 1, "STOP: Close kitchen." } }
};

// Inter-Process Communication Protocol
class IPCProtocol
{
  public:
    IPCProtocol()
        : _comm{ std::make_unique<IOStream>() }
    {
    }
    ~IPCProtocol()
    {
        _comm.release();
    }

    int connect(IIPC &ipc)
    {
        _comm.reset(&ipc);
        return (this->good());
    }

    const std::vector<std::string> &receive() const
    {
        static std::vector<std::string> args;
        char buffer[4096];
        std::string strbuffer;
        std::regex splitter("(\"[^\"]+\"|[^\\s\"]+)");

        args.clear();
        _comm->getline(buffer, 4096);
        strbuffer = std::move(buffer);
        auto it = std::sregex_iterator(strbuffer.begin(), strbuffer.end(), splitter);
        auto end = std::sregex_iterator();
        for (; it != end; ++it) {
            args.push_back(it->str());
        }
        if (!this->validateCommand(args)) {
            args.clear();
        }
        return (args);
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
    std::unique_ptr<IIPC> _comm{ nullptr };

    bool validateCommand(const std::vector<std::string> &args) const
    {
        if (args.size() == 0) {
            std::cerr << "Invalid empty command." << std::endl;
            return (false);
        }
        auto command = commandsList.find(args[0]);
        if (command == commandsList.end()) {
            std::cerr << "Unknown command: '" << args[0] << "'." << std::endl;
            return (false);
        }
        const commandInfo &info = command->second;
        if (args.size() < info.minArgc || (info.maxArgc != 0 && args.size() > info.maxArgc)) {
            std::cerr << "Invalid command syntax." << std::endl;
            return (false);
        }
        return (true);
    }
};

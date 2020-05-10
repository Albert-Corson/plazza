/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenInterface
*/

#pragma once

#include <string_view>
#include <string>
#include <vector>
#include <unordered_map>

#include "deps/OLogStream.hpp"
#include "deps/Socket.hpp"
#include "deps/Exception.hpp"
#include "deps/Process.hpp"
#include "deps/IPC/NamedPipe.hpp"

class KitchenInterface {
private:
    static constexpr std::string_view __fifoName = "fifo.ki";

    using argv_t = std::vector<std::string>;
    using commandPtr_t = bool (KitchenInterface::*)(const argv_t &, std::string &);

    struct commandInfo_t {
        commandPtr_t cmdPtr;
        size_t argc;
    };

    static const std::unordered_map<std::string_view, commandInfo_t> __commands;

    bool _running;
    const std::string _localIPv4;
    const std::string_view _logFilePath;
    OLogStream _logStream;
    Socket _controlSock;
    Socket _clientSock;
    NamedPipe _fifo;
    std::vector<Process> _kitchens;

public:
    class Exception;

    KitchenInterface(const std::string_view &logFile);
    ~KitchenInterface();

    /**
     * @brief accept a new connection and executes orders from it
    **/
    void start();

private:
    bool _createFifo();
    bool _setSighandler();
    void _validateCmd(argv_t &args);

    bool _cmdPing(const argv_t &args, std::string &responseMsg);
    bool _cmdStop(const argv_t &args, std::string &responseMsg);
    bool _cmdStopAll(const argv_t &args, std::string &responseMsg);
    bool _cmdSpawn(const argv_t &args, std::string &responseMsg);
};

class KitchenInterface::Exception : public ::Exception {
public:
    Exception(const std::string &msg);
    ~Exception() override = default;
};

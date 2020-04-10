/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenInterface
*/

#include <signal.h>

#include "KitchenInterface.hpp"
#include "locateKitchenBin.hpp"
#include "deps/utils/StringUtils.hpp"

// PING <pid> -> OK                        / KO
// STOP <pid> -> OK                        / KO
// STOP       -> OK                        / KO
// SPAWN      -> OK <address> <port> <pid> / KO

const std::unordered_map<std::string_view, KitchenInterface::commandInfo_t> KitchenInterface::__commands = {
    { "PING", { &KitchenInterface::_cmdPing, 2 } },
    { "STOP", { &KitchenInterface::_cmdStop, 2 } },
    { "STOP", { &KitchenInterface::_cmdStopAll, 1 } },
    { "SPAWN", { &KitchenInterface::_cmdSpawn, 1 } }
};

KitchenInterface::Exception::Exception(const std::string &msg)
    : ::Exception("KitchenInterface::Exception: " + msg)
{
}

KitchenInterface::KitchenInterface(const std::string_view &logFile)
    : _running(false)
    , _localIPv4(inet_ntoa(Socket::localinfo().sin_addr))
    , _logFilePath(logFile)
    , _logStream(logFile)
{
    _controlSock.listen(0, INADDR_ANY, 1);
    if (!_controlSock.good() || !_setSighandler() || !_createFifo())
        throw KitchenInterface::Exception("failed initialize kitchen interface");

    std::string hostAddr = _localIPv4 + ' ' + std::to_string(ntohs(_controlSock.info().sin_port));
    std::cout << hostAddr << std::endl;
    _logStream.log("Kitchen interface opened on " + hostAddr);
}

KitchenInterface::~KitchenInterface()
{
    int status = 0;

    while (wait(&status) > 0);
    _logStream.log("Kitchen interface closed\n");
}

void KitchenInterface::start()
{
    _clientSock = std::move(_controlSock.accept());
    if (!_clientSock.good())
        throw KitchenInterface::Exception("failed to accept incoming connection");

    _clientSock.write("OK\n", 3);
    _logStream.log("Reception connected");
    _running = true;
    std::string buffer;
    argv_t args;
    while (_running && _clientSock.getline(buffer)) {
        StringUtils::strtab(buffer, args);
        _validateCmd(args);
    }
    if (_running)
        _logStream.log("Reception disconnected");
}

bool KitchenInterface::_createFifo()
{
    return (_fifo.open(__fifoName.data()));
}

bool KitchenInterface::_setSighandler()
{
    struct sigaction newhandler;
    newhandler.sa_handler = SIG_IGN;
    sigemptyset(&newhandler.sa_mask);
    newhandler.sa_flags = 0;
    return (sigaction(SIGCHLD, &newhandler, NULL) == 0);
}

void KitchenInterface::_validateCmd(argv_t &args) 
{
    std::string responseMsg = "command not found";
    bool status = false;

    for (const auto &it : __commands) {
        if (it.first == args[0] && it.second.argc == args.size()) {
            status = (this->*it.second.cmdPtr)(args, responseMsg);
            break;
        }
    }
    responseMsg = (status ? "OK " : "KO ") + responseMsg + "\n";
    _clientSock.write(responseMsg.c_str(), responseMsg.size());
}

bool KitchenInterface::_cmdPing(const argv_t &args, std::string &responseMsg)
{
    pid_t pid = 0;

    try {
        pid = std::stoi(args[1]);
    } catch (...) {
        responseMsg = "invalid <pid> format";
        return (false);
    }
    for (auto it = _kitchens.begin(); it != _kitchens.end(); ++it) {
        if (it->getPid() == pid) {
            if (it->isAlive())
                return (true);
            _kitchens.erase(it);
            return (false);
        }
    }
    responseMsg = "<pid> not found";
    return (false);
}

bool KitchenInterface::_cmdStop(const argv_t &args, std::string &responseMsg)
{
    pid_t pid = 0;

    try {
        pid = std::stoi(args[1]);
    } catch (...) {
        responseMsg = "invalid <pid> format";
        return (false);
    }
    for (auto it = _kitchens.begin(); it != _kitchens.end(); ++it) {
        if (it->getPid() == pid) {
            it->join();
            _kitchens.erase(it);
            return (true);
        }
    }
    responseMsg = "<pid> not found";
    return (false);
}

bool KitchenInterface::_cmdStopAll(const argv_t &args, std::string &responseMsg)
{
    _running = false;
    for (const auto &it : _kitchens)
        it.join();
    return (true);
}

bool KitchenInterface::_cmdSpawn(const argv_t &args, std::string &responseMsg)
{
    Process kitchen;

    pid_t pid = kitchen.exec(locateKitchenBin().c_str(), "--network", __fifoName.data(), _logFilePath.data());
    if (pid < 0) {
        responseMsg = "fork failed";
        return (false);
    }
    in_port_t bindedPort = 0;
    _fifo.receive((char *)&bindedPort, sizeof(bindedPort));
    responseMsg = _localIPv4 + " " + std::to_string(ntohs(bindedPort)) + " " + std::to_string(pid);
    _kitchens.emplace_back(std::move(kitchen));
    return (true);
}

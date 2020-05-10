/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main
*/

#include <list>
#include <string_view>
#include <algorithm>

#include "deps/Socket.hpp"
#include "deps/IPC/NamedPipe.hpp"
#include "deps/IPC/Network.hpp"
#include "deps/IPC/IPCProtocol.hpp"
#include "Kitchen.hpp"

static void help(const char *binName)
{
    std::cerr << "USAGE: " << binName << " [fifoPath [logFile]]" << std::endl
              << "\t--network   -N: start the kitchen in network mode, in which case" << std::endl
              << "\t\t\tit needs the `fifoPath` (as the first argument other than --network)" << std::endl
              << "\t--help      -h: show this menu" << std::endl
              << std::endl
              << "\tIf no arguments are provided, stdin and stdout are used." << std::endl;
}

static std::unique_ptr<IPCProtocol> initNetworkIPC(const std::string_view &fifoPath)
{
    NamedPipe fifo(fifoPath.data());
    Socket sock;
    in_port_t bindedPort = 0;

    sock.listen(0, INADDR_ANY, 1);
    bindedPort = sock.info().sin_port;
    fifo.send((char *)&bindedPort, sizeof(bindedPort));
    std::shared_ptr<Network> network = std::make_shared<Network>(sock.accept());
    return (std::make_unique<IPCProtocol>(network));
}

static std::unique_ptr<IPCProtocol> initNamedPipeIPC(const std::string_view &fifoPath)
{
    std::shared_ptr<NamedPipe> pipe = std::make_shared<NamedPipe>();

    if (!pipe->open(fifoPath.data())) {
        std::cerr << "`" << fifoPath << "`: couldn't open named pipe: " << strerror(errno) << std::endl;
        return (nullptr);
    }
    return (std::make_unique<IPCProtocol>(pipe));
}

static std::unique_ptr<IPCProtocol> initIPC(std::list<std::string_view> &argvList)
{
    bool network = false;
    auto it = std::find_if(argvList.begin(), argvList.end(), [](const auto &elem) {
        return (elem == "--network" || elem == "-N");
    });

    if (it != argvList.end()) {
        if (argvList.size() < 2)
            return (nullptr);
        argvList.erase(it);
        network = true;
    }
    if (argvList.size() != 0) {
        std::string_view fifoPath = argvList.front();
        argvList.pop_front();
        if (network)
            return (initNetworkIPC(fifoPath));
        else
            return (initNamedPipeIPC(fifoPath));
    }
    return (std::make_unique<IPCProtocol>());
}

int main(int argc, char const *argv[])
{
    std::list<std::string_view> argvList;

    for (int i = 0; i < argc; ++i) {
        if (!strcasecmp("-h", argv[i]) || !strcasecmp("--help", argv[i])) {
            help(argv[0]);
            return (1);
        }
    }
    for (int i = 1; i < argc; ++i)
        argvList.emplace_back(argv[i]);
    std::unique_ptr<IPCProtocol> ipc = initIPC(argvList);
    if (ipc == nullptr || !ipc->good())
        return (1);
    try {
        Kitchen kitchen(ipc, argvList.size() ? argvList.front() : "");
        kitchen.start();
    } catch (const std::exception &err) {
        std::cerr << "Kitchen fatal error:" << std::endl
                  << "\t" << err.what() << std::endl;
        return (1);
    } catch (...) {
        std::cerr << "Kitchen fatal error" << std::endl;
        return (1);
    }
    return (0);
}

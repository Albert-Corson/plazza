/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main
*/

#include "deps/IPC/NamedPipe.hpp"
#include "deps/IPC/IPCProtocol.hpp"
#include "Kitchen.hpp"

static void help(const char *binName)
{
    std::cerr << "USAGE: " << binName << " [fifoPath] [logFile]" << std::endl
              << "\tIf no arguments are given, stdin and stdout are used." << std::endl;
}

static std::unique_ptr<IPCProtocol> initIPC(int argc, char const *argv[])
{
    std::unique_ptr<IPCProtocol> ipc = std::make_unique<IPCProtocol>();
    std::shared_ptr<NamedPipe> pipe = std::make_shared<NamedPipe>();

    if (argc >= 2) {
        if (!pipe->open(argv[1])) {
            std::cerr << "Couldn't open named pipe: " << strerror(errno) << std::endl;
            return (nullptr);
        }
        ipc->connect(pipe);
    }
    return (ipc);
}

int main(int argc, char const *argv[])
{
    std::ofstream log;

    for (int i = 0; i < argc; ++i) {
        if (!strcasecmp("-h", argv[i]) || !strcasecmp("--help", argv[i])) {
            help(argv[0]);
            return (1);
        }
    }
    std::unique_ptr<IPCProtocol> ipc = initIPC(argc, argv);
    if (argc > 3 || ipc == nullptr || !ipc->good() || !log.good()) {
        help(argv[0]);
        return (1);
    }
    try {
        Kitchen kitchen(ipc, argc == 3 ? argv[2] : "");
        kitchen.start();
    } catch (const std::exception &err) {
        std::cerr << "Kitchen fatal error:" << std::endl
                  << "\t" << err.what() << std::endl;
        return (1);
    }
    return (0);
}

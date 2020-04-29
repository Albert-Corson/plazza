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

int main(int argc, char const *argv[])
{
    std::ofstream log;
    bool running = true;
    NamedPipe pipe;
    IPCProtocol io;

    for (int i = 0; i < argc; ++i) {
        if (!strcasecmp("-h", argv[i]) || !strcasecmp("--help", argv[i])) {
            help(argv[0]);
            return (0);
        }
    }
    log.copyfmt(std::cout);
    if (argc >= 2) {
        if (!pipe.open(argv[1])) {
            log << "Couldn't open named pipe: " << strerror(errno) << std::endl;
            return (84);
        }
        io.connect(pipe);
    }
    if (argc == 3) {
        log.open(argv[2]);
    }
    if (argc > 3 || !io.good() || !log.good()) {
        help(argv[0]);
        return (84);
    }
    Kitchen kitchen(io);
    kitchen.run();
    return (0);
}

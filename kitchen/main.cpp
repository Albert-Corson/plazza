/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main
*/

#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>
#include "deps/IPC/NamedPipe.hpp"
#include "deps/IPC/IPCProtocol.hpp"

static void help(const char *binName)
{
    std::cerr << "USAGE: " << binName << " [fifoPath] [logFile]" << std::endl
              << "\tIf no arguments are given, stdin and stdout are used." << std::endl;
}

int main(int argc, char const *argv[])
{
    IPCProtocol io;
    std::ofstream log;
    bool running = true;
    NamedPipe pipe;

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
    while (running) {
        const auto &command = io.receive();
        for (auto it : command)
            std::cout << it << std::endl;
        if (command[0] == "STOP")
            running = false;
    }
    return (0);
}

/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main
*/

#include <iostream>
#include "deps/Exception.hpp"
#include "deps/IPC/NamedPipe.hpp"
#include "deps/IPC/IPCProtocol.hpp"

static void help(const char *binName)
{
    std::cerr << "USAGE: " << binName << " <multiplier> <cooks> <refill>" << std::endl
              << "\tmultiplier\tcooking time multiplier" << std::endl
              << "\tcooks\tnumber of cooks per kitchen" << std::endl
              << "\trefill\ttime interval between ingredients stocks refills (in ms)" << std::endl;
}

int main(int argc, char const *argv[])
{
    if (argc != 4) {
        help(argv[0]);
        return (84);
    }

    IPCProtocol comm;
    std::shared_ptr<NamedPipe> pipe = std::make_shared<NamedPipe>("test.fifo");

    pipe->make();
    comm.connect(pipe);
    comm.send("INIT", argv[1], argv[2], argv[3]);
    comm.send("STOP");
    pipe->remove();
    return (0);
}
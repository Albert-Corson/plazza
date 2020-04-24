/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main
*/

#include <iostream>

static void help(const char *binName)
{
    std::cerr << "USAGE: " << binName << " [fifoPath logFile]" << std::endl
              << "\tIf no arguments are given, stdin and stdout are used." << std::endl;
}

int main(int argc, char const *argv[])
{
    FILE *in = stdin;
    FILE *out = stdout;
    FILE *log = stdout;

    if (argc == 3) {
        in = fopen(argv[1], "ra");
        out = in;
        log = fopen(argv[2], "a");
    }
    if  (!in || !out || !log || (argc != 1 && argc != 3)) {
        help(argv[0]);
        return (1);
    }
}

/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main
*/

#include "main.hpp"

int main(int argc, char const **argv)
{
    try {
        main_reception(argc, argv);
    } catch (int err) {
        return (err);
    }
    return (0);
}

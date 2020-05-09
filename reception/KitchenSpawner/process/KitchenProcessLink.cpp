/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenProcessLink
*/

#include "KitchenProcessLink.hpp"

void KitchenProcessLink::waitstop()
{
    pid_t pid = _process.getPid();

    if (pid == -1)
        return;
    waitpid(pid, NULL, 0);
}

bool KitchenProcessLink::isAlive()
{
    return (_process.isAlive());
}

Process &KitchenProcessLink::getProcess()
{
    return (_process);
}
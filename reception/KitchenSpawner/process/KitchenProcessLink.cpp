/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenProcessLink
*/

#include "KitchenProcessLink.hpp"

bool KitchenProcessLink::isAlive() const
{
    return (_process.isAlive());
}

Process &KitchenProcessLink::getProcess()
{
    return (_process);
}
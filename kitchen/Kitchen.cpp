/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(const std::chrono::milliseconds cookingMutliplier, const size_t maxCooks, const std::chrono::milliseconds restockDelay)
    : _cookingMutliplier(cookingMutliplier)
    , _restockDelay(restockDelay)
    , _maxCooks(maxCooks)
{
}

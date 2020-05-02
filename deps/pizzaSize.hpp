/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** kitchenSize
*/

#pragma once

#include <unordered_map>
#include <string>

enum class pizzaSize_t : int {
    UNDEF,
    S,
    M,
    L,
    XL,
    XXL
};

const std::unordered_map<pizzaSize_t, std::string> pizzaSizeStr = {
    { pizzaSize_t::UNDEF, "UNDEFINED" },
    { pizzaSize_t::S, "S" },
    { pizzaSize_t::M, "M" },
    { pizzaSize_t::L, "L" },
    { pizzaSize_t::XL, "XL" },
    { pizzaSize_t::XXL, "XXL" }
};

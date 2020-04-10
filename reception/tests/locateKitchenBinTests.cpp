/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** locateKitchenBinTests
*/

#include <criterion/criterion.h>
#include "locateKitchenBin.hpp"

Test(goodLocation, locateKitchenBinTests)
{
    cr_assert_str_eq(locateKitchenBin("/home").c_str(), "/home");
}

Test(badLocation, locateKitchenBinTests)
{
    cr_assert_str_eq(locateKitchenBin(nullptr).c_str(), "bin/kitchen");
}
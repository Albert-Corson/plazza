/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** PizzaMenuTests
*/

#include <criterion/criterion.h>
#include "PizzaMenu/PizzaMenu.hpp"

Test(correctPath, PizzaMenu)
{
    bool err = false;

    try {
        PizzaMenu pizzas("./pizzas");
    } catch (...) {
        err = true;
    }
    cr_assert_eq(err, false);
}

Test(badPath, PizzaMenu)
{
    bool err = false;

    try {
        PizzaMenu pizzas("");
    } catch (...) {
        err = true;
    }
    cr_assert_eq(err, true);
}

Test(goodName, isGoodPizzaName)
{
    PizzaMenu pizzas("./pizzas");

    cr_assert_eq(pizzas.isGoodPizzaName("regina"), true);
}

Test(badName, isGoodPizzaName)
{
    PizzaMenu pizzas("./pizzas");

    cr_assert_eq(pizzas.isGoodPizzaName("ananas"), false);
}
/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenManagerTests
*/

#include <criterion/criterion.h>
#include "KitchenManager/KitchenManager.hpp"
#include "PizzaMenu/PizzaMenu.hpp"

Test(simpleConstructorInitialization, KitchenManager)
{
    bool err = false;

    try {
        PizzaMenu menu("./pizzas");
        KitchenManager manager(2, 5, 2000, menu);
    } catch (...) {
        err = true;
    }
    cr_assert_eq(err, false);
}
/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ReceptionTests
*/

#include <criterion/criterion.h>
#include "Reception.hpp"

Test(simpleConstructor, Reception)
{
    bool err = false;

    try {
        Reception panel(2, 5, 2000);
    } catch (...) {
        err = true;
    }
    cr_assert_eq(err, false);
}
/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** pizzas
*/

#ifndef PIZZAS_HPP_
#define PIZZAS_HPP_

class Pizza
{
    enum PizzaType
    {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum PizzaSize
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };
};

#endif /* !PIZZAS_HPP_ */
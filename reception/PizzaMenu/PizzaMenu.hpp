/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** PizzaMenu
*/

#pragma once

#include <vector>

#include "deps/plazza/Pizza.hpp"
#include "deps/Exception.hpp"

class PizzaMenu : public std::vector<Pizza> {
    public:
        class Exception;

        PizzaMenu(const std::string &configsFolderPath);
        PizzaMenu() = default;
        ~PizzaMenu() = default;

        bool loadConfigs(const std::string &folderPath);
};

class PizzaMenu::Exception : public ::Exception {
    public:
        Exception(const std::string &msg);
        ~Exception() override = default;
};
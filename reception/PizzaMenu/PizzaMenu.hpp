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

        /**
         * @brief parses all 'X.conf' files located in `configsFolderPath`
         * 
         * @throw PizzaMenu::Exception in case of error
        **/
        PizzaMenu(const std::string &configsFolderPath);
        PizzaMenu() = default;
        ~PizzaMenu() = default;

        /**
         * @brief parses all 'X.conf' files located in `folderPath`
         * 
         * @return bool error/success
        **/
        bool loadConfigs(const std::string &folderPath);

        /**
         * @brief Check if the 'buffer' is a valid Pizza
        **/
        bool isGoodPizzaName(const std::string &buffer);
};

class PizzaMenu::Exception : public ::Exception {
    public:
        Exception(const std::string &msg);
        ~Exception() override = default;
};

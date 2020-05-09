/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** PizzaMenu
*/

#include <filesystem>

#include "PizzaMenu.hpp"

PizzaMenu::Exception::Exception(const std::string &msg)
    : ::Exception("PizzaMenu::Exception: " + msg)
{
}

PizzaMenu::PizzaMenu(const std::string &configsFolderPath) 
{
    if (!loadConfigs(configsFolderPath))
        throw PizzaMenu::Exception("constructor: an error occurred while loading config files");
}

bool PizzaMenu::loadConfigs(const std::string &folderPath) 
{
    Pizza buffer;
    std::filesystem::path currFile;

    for (const auto &it : std::filesystem::directory_iterator(folderPath)) {
        if (!it.is_regular_file() || it.path().extension() != std::filesystem::path(".conf"))
            continue;
        currFile = it.path();
        if (!buffer.parseFromFile(currFile.stem().c_str(), currFile.string()))
            return (false);
        push_back(buffer);
    }
    return (true);
}

bool PizzaMenu::isGoodPizzaName(const std::string &buffer)
{
    for (const auto &it : *this) {
        if (buffer == it.getName())
            return (true);
    }
    return (false);
}
/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** locateKitchenBin
*/

#pragma once

#include <string>

/**
 * @brief returns the stored kitchen bin location
 * 
 * @param newLocation updates the the path if provided
 * @return const std::string &
**/
const std::string &locateKitchenBin(const char *newLocation = nullptr);

/**
 * @brief updates the locateKitchenBin internal path
**/
void updateKitchenBinLocation();

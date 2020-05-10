/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IKitchenSpawner
*/

#pragma once

#include <vector>
#include <memory>

class Pizza;
class IKitchenLink;

class IKitchenSpawner
{
public:
    virtual ~IKitchenSpawner() = default;

    virtual std::shared_ptr<IKitchenLink> spawn() = 0;
};

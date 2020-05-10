/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main_reception
*/

#ifndef MAIN_RECEPTION_HPP_
#define MAIN_RECEPTION_HPP_

#include <string>
#include <memory>

#include "deps/OLogStream.hpp"
#include "PizzaMenu/PizzaMenu.hpp"
#include "KitchenManager/KitchenManager.hpp"
#include "KitchenSpawner/process/KitchenProcessSpawner.hpp"

class Reception
{
public:
    Reception(unsigned int timeMultiplier, unsigned int cooksPerKitchen, unsigned int restoreDelay);
    ~Reception();

    void start(void);
    void parseOrders(std::string buffer);
    void sendToKitchen(void);

protected:
    OLogStream _logStream;
    PizzaMenu _pizzaMenu;
    std::string _tempPizzaName;
    Pizza::psize _tempPizzaSize;
    int _tempPizzaOrder;
    KitchenManager _kitchenManager;
};

#endif /* !MAIN_RECEPTION_HPP_ */
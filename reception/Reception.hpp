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

protected:
    using argv_t = std::vector<std::string>;
    using commandPtr_t = void (Reception::*)(const argv_t &);

    static const std::unordered_map<std::string_view, commandPtr_t> __commands;

    bool _running;
    OLogStream _logStream;
    PizzaMenu _pizzaMenu;
    std::string _tempPizzaName;
    Pizza::psize _tempPizzaSize;
    int _tempPizzaOrder;
    std::unique_ptr<KitchenManager> _kitchenManager;

    bool _parseCmd(const std::string &buffer);
    void _parseOrders(std::string &buffer);
    void _sendToKitchen(void);

    void _cmdExit(const argv_t &args);
    void _cmdStatus(const argv_t &args);
    void _cmdConnect(const argv_t &args);
};

#endif /* !MAIN_RECEPTION_HPP_ */
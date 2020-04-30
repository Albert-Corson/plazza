/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#pragma once

#include <string_view>
#include <unordered_map>

#include "deps/IPC/IPCProtocol.hpp"
#include "deps/Exception.hpp"
#include "deps/Clock.hpp"
#include "Pizza.hpp"
#include "Fridge.hpp"
#include "Cook.hpp"
#include "OrderQueue.hpp"

class Kitchen {
    public:
        class Exception;

        Kitchen(std::unique_ptr<IPCProtocol> &IPC);

        void start();
        void stop();

    private:
        using argv_t = std::vector<std::string>;
        using commandPtr_t = bool (Kitchen::*)(const argv_t &);

        struct commandInfo_t {
            commandPtr_t cmdPtr;
            size_t minArgc;
            size_t maxArgc;
            std::string_view usage;
        };

        static const std::unordered_map<std::string_view, commandInfo_t> __commands;

        std::unique_ptr<IPCProtocol> _IPC;
        std::shared_ptr<Fridge> _fridge;
        std::shared_ptr<OrderQueue> _orderQueue;
        bool _running;

        float _cookTimeMultiplier;
        size_t _maxOrderQueue;
        std::vector<Pizza> _recipe;
        std::vector<Cook> _cooks;

        commandPtr_t _validateCommand(const argv_t &argv);
        void _errorResponse(const std::string_view &message, const argv_t &failedCmd = {});
        void _successResponse();
        bool _help(const argv_t &argv = {});
        bool _start(const argv_t &argv);
        bool _newRecipe(const argv_t &argv);
        bool _order(const argv_t &argv);
        bool _stop(const argv_t &argv = {});
};

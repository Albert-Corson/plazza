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
#include "Log.hpp"

class Kitchen {
    public:
        class Exception;

        Kitchen(std::unique_ptr<IPCProtocol> &IPC, const std::string_view &logFile);
        ~Kitchen();

        void start();
        void stop();

    private:
        using argv_t = std::vector<std::string>;
        using commandPtr_t = bool (Kitchen::*)(const argv_t &, std::string &);

        struct commandInfo_t {
            commandPtr_t cmdPtr;
            size_t minArgc;
            size_t maxArgc;
            std::string_view usage;
        };

        static const millisec_t __timeout;
        static const std::unordered_map<std::string_view, commandInfo_t> __commands;

        std::unique_ptr<IPCProtocol> _IPC;

        Thread _manager;
        std::shared_ptr<Log> _logStream;
        std::shared_ptr<Fridge> _fridge;
        std::shared_ptr<OrderQueue> _orderQueue;
        bool _running;

        float _cookTimeMultiplier;
        size_t _maxOrderQueue;
        std::vector<Pizza> _recipe;
        std::vector<std::unique_ptr<Cook>> _cooks;

        commandPtr_t _validateCommand(const argv_t &argv);
        void _errorResponse(const std::string_view &message, const argv_t &failedCmd = {});
        void _successResponse(const std::string &message);
        void _startManager();

        bool _cmdHelp(const argv_t &argv, std::string &responseMsg);
        bool _cmdStart(const argv_t &argv, std::string &responseMsg);
        bool _cmdNewRecipe(const argv_t &argv, std::string &responseMsg);
        bool _cmdOrder(const argv_t &argv, std::string &responseMsg);
        bool _cmdStatus(const argv_t &argv, std::string &responseMsg);
        bool _cmdStop(const argv_t &argv, std::string &responseMsg);
};

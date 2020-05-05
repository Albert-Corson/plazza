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
#include "Pizza/Pizza.hpp"
#include "Fridge/Fridge.hpp"
#include "Cook/Cook.hpp"
#include "OrderQueue/OrderQueue.hpp"
#include "Log/Log.hpp"

class Kitchen {
    public:
        class Exception;

        /**
         * @brief Construct a new Kitchen object
         * 
         * @param IPC communication device to receive orders from
         * @param logFile file to log done orders to
        **/
        Kitchen(std::unique_ptr<IPCProtocol> &IPC, const std::string_view &logFile);
        ~Kitchen();

        /**
         * @brief starts the CLI/communication protocol
         * the kitchen starts reading onto the IPC to execute orders and give responses
        **/
        void start();

        /**
         * @brief stops the kitchen and its threads
        **/
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

        /**
         * @brief checks if a given command exists and returns it
         * 
         * @param argv the command-line to execute, separated into a word array, argv[0] is the name of the command
         * @return commandPtr_t method pointer to the corresponding command, or nullptr for errors
        **/
        commandPtr_t _validateCommand(const argv_t &argv);

        /**
         * @brief sends an error (KO) to the IPC along with the error `message`
         * if compiled in debug mode, the failed command is printed to stderr
         * 
         * @param message error message
         * @param failedCmd the failed command-line, separated into a word array
        **/
        void _errorResponse(const std::string_view &message, const argv_t &failedCmd = {});

        /**
         * @brief sends a success reponse (OK) to the IPC along with the `message`
        **/
        void _successResponse(const std::string &message);

        /**
         * @brief starts the kitchen manage thread, responsible for restocking, timeouts and order queue clearing
        **/
        void _startManager();

        /**
         * @brief executes the "HELP" command
         * format ex: HELP
         * 
         * @param argv the command-line, separated into a word array
         * @param responseMsg a string reference to fill with a reponse message
         * @return bool true on success, false on error
        **/
        bool _cmdHelp(const argv_t &argv, std::string &responseMsg);

        /**
         * @brief executes the "START" command
         * format ex: START <multiplier> <cooks> <refill_rate_ms>
         * 
         * @param argv the command-line, separated into a word array
         * @param responseMsg a string reference to fill with a reponse message
         * @return bool true on success, false on error
        **/
        bool _cmdStart(const argv_t &argv, std::string &responseMsg);

        /**
         * @brief executes the "NEW_RECIPE" command
         * format ex: NEW_RECIPE <name> <cook_time_ms> [<ingredient> <amount>]...
         * 
         * @param argv the command-line, separated into a word array
         * @param responseMsg a string reference to fill with a reponse message
         * @return bool true on success, false on error
        **/
        bool _cmdNewRecipe(const argv_t &argv, std::string &responseMsg);

        /**
         * @brief executes the "ORDER" command
         * format ex: ORDER <name> <size>
         * 
         * @param argv the command-line, separated into a word array
         * @param responseMsg a string reference to fill with a reponse message
         * @return bool true on success, false on error
        **/
        bool _cmdOrder(const argv_t &argv, std::string &responseMsg);

        /**
         * @brief executes the "STATUS" command
         * format ex: STATUS [<any>] (If <any> is present, data will be serialized.)
         * 
         * @param argv the command-line, separated into a word array
         * @param responseMsg a string reference to fill with a reponse message
         * @return bool true on success, false on error
        **/
        bool _cmdStatus(const argv_t &argv, std::string &responseMsg);

        /**
         * @brief executes the "STOP" command
         * format ex: STOP
         * 
         * @param argv the command-line, separated into a word array
         * @param responseMsg a string reference to fill with a reponse message
         * @return bool true on success, false on error
        **/
        bool _cmdStop(const argv_t &argv, std::string &responseMsg);
};

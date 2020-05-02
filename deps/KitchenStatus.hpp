/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenStatus
*/

#pragma once

#include <regex>
#include <tuple>

#include "Exception.hpp"
#include "pizzaSize.hpp"

struct KitchenStatus {
    class Exception : public ::Exception {
    public:
        Exception(const std::string &msg)
            : ::Exception("KitchenStatus::Exception: " + msg)
        {
        }
        ~Exception() override = default;
    };

    size_t activeCooks = 0;
    size_t totalCooks = 0;
    size_t orderQueueCapacity = 0;
    std::vector<std::tuple<std::string, pizzaSize_t, bool>> orderQueue;

    // returns a string buffer containing the kitchen infos in the following format:
    // <activeCooks> <totalCooks> <orderQueueCapacity>[:<pizza> <size> <status>]...
    const std::string &serialize() const noexcept
    {
        static std::string buffer;

        buffer.clear();
        buffer += std::to_string(activeCooks);
        buffer += ' ';
        buffer += std::to_string(totalCooks);
        buffer += ' ';
        buffer += std::to_string(orderQueueCapacity);
        for (const auto &it : orderQueue) {
            buffer += ':';
            buffer += std::get<0>(it);
            buffer += ' ';
            buffer += pizzaSizeStr.at(std::get<1>(it));
            buffer += ' ';
            buffer += std::to_string(std::get<2>(it));
        }
        return (buffer);
    }

    // parses a string buffer formatted the way of `dump()`'s output
    void deserialize(const std::string &line)
    {
        std::regex format("^ *([0-9]+) +([0-9]+) +([0-9]+)");
        std::smatch matches;

        if (!std::regex_search(line, matches, format))
            throw Exception("deserialize: invalid format");
        try {
            activeCooks = std::stoul(matches.str(1));
            totalCooks = std::stoul(matches.str(2));
            orderQueueCapacity = std::stoul(matches.str(3));

            format = "^ *([A-z0-9_-]+) +([0-5]) +([01])";
            std::string buffer = line;
            for (size_t pos = buffer.find(':'); pos != std::string::npos; pos = buffer.find(':')) {
                buffer = buffer.substr(pos);
                if (!std::regex_search(buffer, matches, format))
                    throw Exception("deserialize: invalid format");
                orderQueue.emplace_back(matches.str(1), pizzaSize_t(std::stoi(matches.str(2))), std::stoi(matches.str(3)));
            }
        } catch (...) {
            throw Exception("deserialize: invalid format");
        }
    }

    // dumps infos in a human-readable format
    void dump(std::ostream &output) const noexcept
    {
        size_t ongoing = 0;

        for (const auto &it : orderQueue) {
            if (std::get<2>(it))
                ++ongoing;
        }
        output << "Cooks: " << totalCooks << " (" << activeCooks << " working)" << std::endl
               << "Orders: " << ongoing << "/" << orderQueue.size() << " ongoing (queue capacity: " << orderQueueCapacity << ")" << std::endl;
        for (const auto &it : orderQueue) {
            output << "\t" << std::get<0>(it) << " " << pizzaSizeStr.at(std::get<1>(it)) << ": ";
            if (std::get<2>(it))
                output << "ongoing";
            else
                output << "awaiting";
            output << std::endl;
        }
    }
};

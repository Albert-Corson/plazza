/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenStatus
*/

#pragma once

#include <regex>

#include "Exception.hpp"

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
    std::vector<std::pair<std::string, bool>> orderQueue;

    // returns a string buffer containing the kitchen infos in the following format:
    // <activeCooks> <totalCooks> <orderQueueCapacity>[:<pizza> <status>]...
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
            buffer += it.first;
            buffer += ' ';
            buffer += std::to_string(it.second);
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

            format = "^ *([A-z0-9_-]+) +([01])";
            std::string buffer = line;
            for (size_t pos = buffer.find(':'); pos != std::string::npos; pos = buffer.find(':')) {
                buffer = buffer.substr(pos);
                if (!std::regex_search(buffer, matches, format))
                    throw Exception("deserialize: invalid format");
                orderQueue.emplace_back(matches.str(1), std::stoi(matches.str(2)));
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
            if (it.second)
                ++ongoing;
        }
        output << "Cooks: " << totalCooks << " (" << activeCooks << " working)" << std::endl
               << "Orders: " << ongoing << "/" << orderQueue.size() << " ongoing (queue capacity: " << orderQueueCapacity << ")" << std::endl;
        for (const auto &it : orderQueue) {
            output << "\t" << it.first << ": ";
            if (it.second)
                output << "ongoing";
            else
                output << "awaiting";
            output << std::endl;
        }
    }
};

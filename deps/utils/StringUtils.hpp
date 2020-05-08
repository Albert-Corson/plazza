/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** StringUtils
*/

#pragma once

#include <regex>
#include <vector>
#include <string>

class StringUtils
{
public:
    StringUtils() = delete;
    ~StringUtils() = default;

    /**
     * @brief fill vector with args parsed from input string
     * @param input input string
     * @param buffer vector to be filled
     */
    static bool strtab(const std::string &input, std::vector<std::string> &buffer)
    {
        std::regex splitter("(\"[^\"]+\"|[^\\s\"]+)");

        buffer.clear();
        auto it = std::sregex_iterator(input.begin(), input.end(), splitter);
        auto end = std::sregex_iterator();
        for (; it != end; ++it) {
            buffer.emplace_back(std::move(it->str()));
        }
        return (true);
    }
};

/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#pragma once

#include <string_view>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <regex>
#include <unordered_map>

#include "deps/Exception.hpp"
#include "deps/Clock.hpp"
#include "deps/plazza/Ingredient.hpp"

class Pizza {
    public:
        class Exception : public ::Exception {
            public:
                Exception(const std::string &msg)
                    : ::Exception("Pizza::Exception: " + msg)
                {
                }
                ~Exception() override = default;
        };

        enum pstatus : int {
            ST_IDLE,
            ST_COOKING,
            ST_COOKED,
        };

        enum psize : int {
            SZ_UNDEF,
            SZ_S,
            SZ_M,
            SZ_L,
            SZ_XL,
            SZ_XXL
        };

        /**
         * @brief get the stringified value of `size`
        **/
        static const std::string &getSizeStr(psize size) noexcept
        {
            static const std::unordered_map<psize, std::string> sizeStr = {
                { psize::SZ_UNDEF, "UNDEFINED" },
                { psize::SZ_S, "S" },
                { psize::SZ_M, "M" },
                { psize::SZ_L, "L" },
                { psize::SZ_XL, "XL" },
                { psize::SZ_XXL, "XXL" }
            };
            return (sizeStr.at(size));
        }

        /**
         * @brief get the enum value of the `size` string
        **/
        static psize getSizeFromStr(const std::string size) noexcept
        {
            static const std::unordered_map<std::string, psize> sizeFromStr = {
                { "UNDEFINED", psize::SZ_UNDEF },
                { "S", psize::SZ_S },
                { "M", psize::SZ_M },
                { "L", psize::SZ_L },
                { "XL", psize::SZ_XL },
                { "XXL", psize::SZ_XXL }
            };
            for (const auto &it : sizeFromStr) {
                if (it.first == size)
                    return (it.second);
            }
            return (SZ_UNDEF);
        }

        Pizza()
            : _size(psize::SZ_UNDEF)
            , _cookTime(0)
            , _status(ST_IDLE)
        {
        }

        /**
         * @brief Construct a new Pizza object
         * 
         * @param name name of the pizza
         * @param cookTime its cooking time
         * @param size its size, undefined by default
        **/
        Pizza(const std::string_view &name, millisec_t cookTime, psize size = psize::SZ_UNDEF)
            : _name(name.data())
            , _size(size)
            , _cookTime(cookTime)
            , _status(ST_IDLE)
        {
        }

        /**
         * @brief Construct a new Pizza object from a config file
         * 
         * @param pizzaName name of the new pizza
         * @param filePath path to the config file
         * @throw Pizza::Exception in case of parsing errors
        **/
        Pizza(const std::string_view &pizzaName, const std::string &filePath)
            : Pizza()
        {
            if (!parseFromFile(pizzaName, filePath))
                throw Exception("constructor: a parsing error occurred (`" + filePath + "`)");
        }

        Pizza(const Pizza &other)
            : _name(other._name)
            , _cookTime(other._cookTime)
            , _status(other._status)
            , _recipe(other._recipe)
        {
        }

        /**
         * @brief add an `ingredient` to the recipe of the pizza
        **/
        void addIngredientToRecipe(Ingredient &&ingredient)
        {
            auto exists = std::find_if(_recipe.begin(), _recipe.end(), [&ingredient](const auto &elem) {
                return (ingredient.getName() == elem.getName());
            });

            if (exists != _recipe.cend()) {
                *exists = std::move(ingredient);
                return;
            }
            _recipe.emplace_back(std::move(ingredient));
        }

        /**
         * @brief Get the name of the pizza
        **/
        const std::string &getName() const noexcept
        {
            return (_name);
        }

        /**
         * @brief Get the cooking time of the pizza in milliseconds
        **/
        millisec_t getCookTime() const noexcept
        {
            return (_cookTime);
        }

        /**
         * @brief Get the ingredients needed to make this pizza
         * 
         * @return const std::vector<Ingredient> &
        **/
        const std::vector<Ingredient> &getRecipe() const noexcept
        {
            return (_recipe);
        }

        /**
         * @brief Get the status of the pizza
        **/
        pstatus getStatus() const noexcept
        {
            return (_status);
        }

        /**
         * @brief Get the size of the pizza
        **/
        psize getSize() const noexcept
        {
            return (_size);
        }

        /**
         * @brief Set status of the pizza
        **/
        void setStatus(pstatus status) noexcept
        {
            _status = status;
        }

        /**
         * @brief Set the size of the pizza
        **/
        void setSize(psize size) noexcept
        {
            _size = size;
        }

        /**
         * @brief parses a pizza config file
         * 
         * @param filePath path to file to parse
         * @return bool success/error
        **/
        bool parseFromFile(const std::string_view &pizzaName, const std::string &filePath)
        {
            std::ifstream file;
            std::regex format("^[ \t]*([0-9]+)[ \t]+(.*)$");
            std::smatch matches;
            std::string buffer;
            bool check = false;

            try {
                file.open(filePath);
                if (!file.good())
                    return (false);
                while (std::getline(file, buffer)) {
                    if (buffer.find_first_not_of(" \t") == std::string::npos)
                        continue;
                    if (!check) {
                        _cookTime = std::stoul(buffer);
                        check = true;
                    } else if (std::regex_search(buffer, matches, format)) {
                        addIngredientToRecipe(Ingredient(matches.str(2), std::stoul(matches.str(1))));
                    } else {
                        return (false);
                    }
                }
            } catch (...) {
                return (false);
            }
            _name = pizzaName;
            return (true);
        }

    private:
        std::string _name;
        psize _size;
        millisec_t _cookTime;
        pstatus _status;
        std::vector<Ingredient> _recipe;
};

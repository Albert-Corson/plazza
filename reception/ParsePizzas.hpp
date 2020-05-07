/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ParsePizzas
*/

#ifndef PIZZAS_HPP_
#define PIZZAS_HPP_

#include <vector>

class Pizza
{
    protected:
        class PizzaContent
        {
            public:
                std::string _name;
                std::vector<std::string> _ingredients;
                int _timeMultiplier;
        };

        std::vector<PizzaContent> _pizzaList;
        std::vector<std::string> _ingredientList;

    public:
        void add_new_pizza(const std::string &name)
        {
            PizzaContent temp;

            temp._name = name;
            this->_pizzaList.push_back(temp);
        }

        void add_ingredient_to_list(const std::string &name)
        {
            this->_ingredientList.push_back(name);
        }

        int is_new_ingredient_to_list(const std::string &name)
        {
            long unsigned int index = 0;

            while (index < this->_ingredientList.size()) {
                if (name == this->_ingredientList.at(index))
                    return 0;
                ++index;
            }
            return 1;
        }

        void add_new_ingredient_to_pizza(const std::string &ingredient)
        {
            this->_pizzaList.at(this->_pizzaList.size() - 1)._ingredients.push_back(ingredient);
        }

        void add_second_multiplier_to_pizza(int time)
        {
            this->_pizzaList.at(this->_pizzaList.size() - 1)._timeMultiplier = time;
        }

            std::vector<PizzaContent> get_pizzaList(void)
        {
            return (this->_pizzaList);
        }

        bool is_new_pizza(const std::string &name)
        {
            long unsigned int index = 0;
        
            while (index < this->_pizzaList.size()) {
                if (name == this->_pizzaList.at(index)._name)
                    return 0;
                ++index;
            }
            return 1;
        }

        bool is_size_good(const std::string &size)
        {
            if (size == "S" || size == "M" || size == "L"
            || size == "XL" || size == "XXL")
                return 1;
            return 0;
        }

        enum PizzaSize
        {
            S = 1,
            M = 2,
            L = 4,
            XL = 8,
            XXL = 16
        };
};

#endif /* !PIZZAS_HPP_ */
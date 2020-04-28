/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(const double &cookingMutliplier, const size_t &cooks, const millisec_t &restockRate)
    : _cookingMutliplier(cookingMutliplier)
    , _restockRate(restockRate)
    , _maxOrderQueue(cooks)
    , _fridge(std::make_shared<std::vector<ResourceLock<Ingredient>>>())
    , _orderQueue(std::make_shared<ResourceLock<std::list<Pizza>>>())
{
    for (size_t i = 0; i < cooks; ++i) {
        _cooks.emplace_back(cookingMutliplier, _orderQueue, _fridge);
        _cooks[i].getWorking();
    }
}

Kitchen::~Kitchen()
{
    for (auto &it : _cooks)
        it.layOff();
}

void Kitchen::addPizzaToMenu(const std::string_view &pizza, const millisec_t &cookTime, const std::unordered_map<std::string_view, size_t> &ingredients)
{
    for (const auto &it : _menu) {
        if (it.getName() == pizza)
            throw Kitchen::Exception("Pizza already exist: " + std::string(pizza.data()));
    }
    Pizza entry(pizza, cookTime);
    for (const auto &it : ingredients) {
        const auto &check = std::find_if((*_fridge).cbegin(), (*_fridge).cend(), [&it](const auto &curr){
            return (curr->getName() == it.first);
        });
        if (check == (*_fridge).cend())
            (*_fridge).emplace_back(Ingredient(it.first, _restockRate));
        entry.addIngredient(it.first, it.second);
    }
    _menu.emplace_back(std::move(entry));
}

size_t Kitchen::getAvailQueueSize() const noexcept
{
    return (_maxOrderQueue - (*_orderQueue).read().size());
}

void Kitchen::takeOrder(const std::string_view &pizzaName)
{
    const auto &pizza = std::find_if(_menu.cbegin(), _menu.cend(), [&pizzaName](const auto &it) {
        return (it.getName() == pizzaName);
    });

    if (pizza == _menu.cend())
        throw Kitchen::Exception("Unknown pizza");
    if (getAvailQueueSize() == 0)
        throw Kitchen::Exception("Maximum amount of queued orders reached");
    (*_orderQueue).apply([&pizza](auto &queue) {
        queue.push_back(*pizza);
    });
}

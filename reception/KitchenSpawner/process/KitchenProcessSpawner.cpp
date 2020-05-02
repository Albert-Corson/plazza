/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenProcessSpawner
*/

#include "KitchenProcessSpawner.hpp"
#include "KitchenProcessLink.hpp"
#include "deps/IPC/NamedPipe.hpp"

static inline const std::string locateKitchenBin()
{
    return ("bin/kitchen");
}

std::shared_ptr<IKitchenLink> KitchenProcessSpawner::spawn(float multiplier, int cooks, int interval)
{
    static int id = 0;
    std::string name = "fifo" + std::to_string(id);
    while (access(name.c_str(), F_OK) != -1) {
        ++id;
        name = "fifo" + std::to_string(id);
    }
    std::shared_ptr<KitchenProcessLink> link = std::make_unique<KitchenProcessLink>();
    std::shared_ptr<NamedPipe> pipe = std::make_shared<NamedPipe>(name);
    link->getIPC().connect(pipe);

    const std::string &kitchenBin = locateKitchenBin();
    pid_t pid = link->getProcess().exec(kitchenBin.c_str(), name.c_str(), NULL);
    if (pid == -1)
        return (nullptr);
    if (!link->start(multiplier, cooks, interval)) {
        link->stop();
        return (nullptr);
    }
    ++id;
    return (link);
}
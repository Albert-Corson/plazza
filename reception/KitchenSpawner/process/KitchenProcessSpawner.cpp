/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenProcessSpawner
*/

#include <signal.h>
#include "KitchenProcessSpawner.hpp"
#include "KitchenProcessLink.hpp"
#include "deps/IPC/NamedPipe.hpp"

static struct sigaction oldhandler;

static void sig()
{
    struct sigaction newhandler;
    newhandler.sa_handler = SIG_IGN;
    sigemptyset(&newhandler.sa_mask);
    newhandler.sa_flags = 0;
    sigaction(SIGCHLD, &newhandler, NULL);
}

static inline const std::string locateKitchenBin()
{
    return ("bin/kitchen");
}

std::shared_ptr<IKitchenLink> KitchenProcessSpawner::spawn(float multiplier, int cooks, int interval,
                                                           const std::vector<Pizza> &pizzaMenu)
{
    static int id = 0;
    std::string name = "fifo" + std::to_string(id);
    while (access(name.c_str(), F_OK) != -1) {
        ++id;
        name = "fifo" + std::to_string(id);
    }
    std::shared_ptr<KitchenProcessLink> link = std::make_shared<KitchenProcessLink>();
    std::shared_ptr<NamedPipe> pipe = std::make_shared<NamedPipe>(name);
    link->getIPC().connect(pipe);
    sig();
    const std::string &kitchenBin = locateKitchenBin();
    pid_t pid = link->getProcess().exec(kitchenBin.c_str(), name.c_str(), NULL);
    if (pid == -1)
        return (nullptr);
    if (!link->start(multiplier, cooks, interval, pizzaMenu)) {
        link->stop();
        return (nullptr);
    }
    ++id;
    return (link);
}
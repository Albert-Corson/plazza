/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenProcessSpawner
*/

#include <signal.h>

#include "KitchenProcessSpawner.hpp"
#include "KitchenProcessLink.hpp"
#include "logfile.hpp"
#include "locateKitchenBin.hpp"

static struct sigaction oldhandler;

static void sig()
{
    struct sigaction newhandler;
    newhandler.sa_handler = SIG_IGN;
    sigemptyset(&newhandler.sa_mask);
    newhandler.sa_flags = 0;
    sigaction(SIGCHLD, &newhandler, NULL);
}

std::shared_ptr<IKitchenLink> KitchenProcessSpawner::spawn()
{
    static int id = 0;
    std::string name = "fifo" + std::to_string(id);
    while (access(name.c_str(), F_OK) != -1) {
        ++id;
        name = "fifo" + std::to_string(id);
    }
    std::shared_ptr<KitchenProcessLink> link = std::make_unique<KitchenProcessLink>(name);
    sig();
    const std::string &kitchenBin = locateKitchenBin();
    pid_t pid = link->getProcess().exec(kitchenBin.c_str(), name.c_str(), LOGFILE);
    if (pid == -1)
        return (nullptr);
    ++id;
    return (link);
}
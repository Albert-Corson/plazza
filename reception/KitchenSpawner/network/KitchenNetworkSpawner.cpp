/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenNetworkSpawner
*/

#include "KitchenNetworkSpawner.hpp"
#include "KitchenNetworkLink.hpp"
#include "deps/utils/StringUtils.hpp"
#include "deps/IPC/Network.hpp"
#include "deps/Socket.hpp"

static inline const std::string locateKitchenBin()
{
    return ("bin/kitchen");
}

KitchenNetworkSpawner::KitchenNetworkSpawner(std::shared_ptr<Socket> interface) 
    : _interface{ interface }
{
}

std::shared_ptr<IKitchenLink> KitchenNetworkSpawner::spawn()
{
    std::string cmd = "SPAWN\n";
    _interface->write(cmd.c_str(), cmd.size());
    std::string BUFFER;
    _interface->getline(BUFFER);
    std::vector<std::string> args;

    StringUtils::strtab(BUFFER, args);
    if (args[0] != "OK") {
        std::cerr << "Couldn't spawn kitchen" << std::endl;
        return (nullptr);
    }
    std::string &address = args[1];
    in_port_t port = htons(std::stoul(args[2]));
    pid_t pid = std::stoul(args[3]);

    return (std::make_shared<KitchenNetworkLink>(_interface, address, port, pid));
}

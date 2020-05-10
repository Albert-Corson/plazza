/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenNetworkLink
*/

#include "KitchenNetworkLink.hpp"

KitchenNetworkLink::KitchenNetworkLink(const std::string &address, in_port_t port, pid_t pid)
    : _id{ pid }
{
    std::shared_ptr<Network> ipc = std::make_shared<Network>();
    Socket &socket = ipc->getSocket();
    socket.connect(port, address.c_str());
    _ipc.connect(ipc);

}

void KitchenNetworkLink::waitstop()
{
    std::string cmd = "STOP " + std::to_string(_id);
    std::string BUFFER;

    _interface.write(cmd.c_str(), cmd.size());
    _interface.getline(BUFFER);
}

bool KitchenNetworkLink::isAlive()
{
    std::string cmd = "PING " + std::to_string(_id);
    std::string BUFFER;

    _interface.write(cmd.c_str(), cmd.size());
    _interface.getline(BUFFER);
    
    if (BUFFER == "OK")
        return true;
    return false;
}

Network &KitchenNetworkLink::getNetwork()
{
    return _network;
}
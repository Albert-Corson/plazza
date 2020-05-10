/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** KitchenNetworkLink
*/

#include "KitchenNetworkLink.hpp"

KitchenNetworkLink::KitchenNetworkLink(std::shared_ptr<Socket> interface, const std::string &address, in_port_t port, pid_t pid)
    : _id { pid }
    , _interface { interface }
{
    std::shared_ptr<Network> ipc = std::make_shared<Network>();
    Socket &socket = ipc->getSocket();
    socket.connect(port, address.c_str());
    _ipc.connect(ipc);
}

void KitchenNetworkLink::waitstop()
{
    std::string cmd = "STOP " + std::to_string(_id) + "\n";
    std::string BUFFER;

    _interface->write(cmd.c_str(), cmd.size());
    _interface->getline(BUFFER);
}

bool KitchenNetworkLink::isAlive()
{
    std::string cmd = "PING " + std::to_string(_id) + "\n";
    std::string BUFFER;

    _interface->write(cmd.c_str(), cmd.size());
    _interface->getline(BUFFER);

    if (BUFFER == "OK")
        return true;
    return false;
}

bool KitchenNetworkLink::kill()
{
    std::string buffer = "STOP " + std::to_string(_id) + "\n";

    _interface->write(buffer.c_str(), buffer.size());
    buffer.clear();
    _interface->getline(buffer);
    if (buffer.substr(0, 2) == "KO")
        return (false);
    return (true);
}

Network &KitchenNetworkLink::getNetwork()
{
    return _network;
}
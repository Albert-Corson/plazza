/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IIPC
*/

#pragma once

#include <fstream>

// Inter-Process Communication interface
class IIPC
{
  public:
    virtual ~IIPC(){};

    // Receive message from communication input
    virtual void receive(char *buffer, std::streamsize size) = 0;
    // Get next line from communication input
    virtual bool getline(std::string &buffer) = 0;
    // Send message to communication output
    virtual void send(const char *buffer, std::streamsize size) = 0;
    // Tell if communication is established successfully
    virtual bool good() const = 0;
};

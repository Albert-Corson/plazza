/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Process
*/

#pragma once

#include "Exception.hpp"
#include <unistd.h>
#include <sys/wait.h>

class Process {
    public:
        class Exception : public ::Exception {
            public:
                Exception(const std::string &msg)
                    : ::Exception("Process::Exception: " + msg)
                {
                }
                ~Exception() override = default;
        };

        Process() = default;
        ~Process() = default;

        pid_t fork()
        {
            _pid = ::fork();
        }
        int join() const
        {
            int status = 0;

            if (_pid < 0)
                throw Process::Exception("No child process started");
            else if (_pid == 0)
                throw Process::Exception("A child process cannot wait for it's parent");
            if (wait(&status) != _pid)
                throw Process::Exception("Couldn't wait for the child process to finish");
            return (status);
        }
        pid_t getPid() const
        {
            return (_pid);
        }

    private:
        pid_t _pid = -1;
};

/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Fork
*/

#pragma once

#include "Exception.hpp"
#include <unistd.h>
#include <sys/wait.h>

class Fork {
    public:
        class Exception : public ::Exception {
            public:
                Exception(const std::string &msg)
                    : ::Exception("Fork::Exception: " + msg)
                {
                }
                ~Exception() override = default;
        };

        Fork()
        {
            _pid = fork();
        }
        ~Fork() = default;

        int join() const
        {
            int status = 0;

            if (_pid == 0)
                throw Fork::Exception("A child process cannot wait for it's parent");
            if (wait(&status) != _pid)
                throw Fork::Exception("Couldn't wait for the child process to finish");
            return (status);
        }
        pid_t getPid() const
        {
            return (_pid);
        }

    private:
        pid_t _pid;
};

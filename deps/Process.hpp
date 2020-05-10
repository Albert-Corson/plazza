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
#include <errno.h>

#include <iostream>

class Process {
public:
    class Exception : public ::Exception {
    public:
        Exception(const std::string &msg)
            : ::Exception("Process::Exception: " + msg)
        {
        }
        Exception(std::string &&msg)
            : ::Exception(std::move("Process::Exception: " + msg))
        {
        }
        ~Exception() override = default;
    };

    Process(const Process &other)
        : _pid(other._pid)
    {
    }

    Process() = default;
    ~Process() = default;

    /**
     * @brief Execute `path` into a fork with all arguments after.
     * 
     * @return pid_t the child process pid
    **/
    template <typename... Args>
    pid_t exec(const char *path, Args &&... args)
    {
        this->fork();
        if (_pid == 0) {
            int status = execl(path, path, args..., NULL);
            exit(status == -1);
        }
        return (_pid);
    }
    /**
     * @brief forks the process
     * 
     * @return pid_t the child pid
    **/
    pid_t fork()
    {
        _pid = ::fork();
        return (_pid);
    }
    /**
     * @brief wait for the child process to finish
     * 
     * @return int the exit status of the child
    **/
    int join() const
    {
        int status = 0;

        if (_pid < 0)
            throw Process::Exception("No child process started");
        else if (_pid == 0)
            throw Process::Exception("A child process cannot wait for it's parent");
        if (wait(&status) != _pid) {
            throw Process::Exception("Couldn't wait for the child process to finish");
        }
        return (status);
    }
    /**
     * @brief checks if the child process is still running
     * 
     * @return bool
    **/
    bool isAlive() const
    {
        errno = 0;
        if (_pid == -1 || ::kill(_pid, 0) == -1)
            return (false);
        return (errno == 0);
    }
    /**
     * @brief tries to kill the process by sending a SIGKILL
     * 
     * @return bool
    **/
    bool kill() const
    {
        errno = 0;
        if (_pid == -1 || ::kill(_pid, SIGKILL) == -1)
            return (false);
        return (errno == 0);
    }
    /**
     * @brief get the pid of the child
     * 
     * @return pid_t
    **/
    pid_t getPid() const
    {
        return (_pid);
    }

private:
    pid_t _pid = -1;
};

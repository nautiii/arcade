/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** ErrorHandling.hpp
*/

#ifndef ERRORHANDLING_HPP
# define ERRORHANDLING_HPP

/** 
 * \file ErrorHandling.hpp
 * \date March 2020
 * \version 0.1
*/

#include <exception>
#include <iostream>
#include <array>
#include <cstdlib>

using namespace std;

static const string &CURRENT_DIR = "./";

static const char *const SFML_ENV_VARIABLE = "DISPLAY";
static const char *const AA_ENV_VARIABLE   = "TERM";

/**
 * \class GameError
 * \brief main error class of arcade project
*/
class GameError : public exception
{
    public:
        enum Flags {
            UNDEFINED,
            ERRARGS,
            ERRENV,
            ERRPATH,
            ERROPEN,
            ERRSYM,
            ERRCREATE,
            TOTAL
        };
        Flags  flag;
        string sym;
    public:
        GameError() noexcept;
        virtual ~GameError() noexcept = default;
    public:
        virtual const char *what() const noexcept;
    private:
        array<string, TOTAL> messages;
};

extern GameError err;

class ArgsError
{
    public:
        ArgsError() noexcept = default;
        ~ArgsError() noexcept = default;
    public:
        static inline void  checkEnv();
        static const string checkArgs(int, const char *);
        static const string checkPath(const char *);
};

#endif
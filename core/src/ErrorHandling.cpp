/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** ErrorHandling.cpp
*/

#include "ErrorHandling.hpp"

GameError err = {};

GameError::GameError() noexcept
    : flag(UNDEFINED), sym("")
{
    messages[UNDEFINED] = "error: undefined error occured.";
    messages[ERRARGS]   = "usage: ./arcade ./path/to/your/library.so";
    messages[ERRPATH]   = "error: dynamic library not found.";
    messages[ERRENV]    = "error: environment variables missing.";
    messages[ERROPEN]   = "error: unable to open dynamic library.";
    messages[ERRSYM]    = "error: unable to found '";
    messages[ERRCREATE] = "error: the dlib instance could not be created.";
}

const char *GameError::what() const noexcept
{
    return messages[flag].c_str();
}

void ArgsError::checkEnv()
{
    if (!getenv(SFML_ENV_VARIABLE) || !getenv(AA_ENV_VARIABLE)) {
        err.flag = GameError::ERRENV;
        throw err;
    }
}

const string ArgsError::checkArgs(const int ac, const char *path)
{
    if (ac ^ 2) {
        err.flag = GameError::ERRARGS;
        throw err;
    }
    checkEnv();
    return checkPath(path);
}

const string ArgsError::checkPath(const char *path)
{
    string spath(path);

    if (spath.compare(0, 2, CURRENT_DIR))
        spath.insert(0, CURRENT_DIR);
    if (spath.compare(0, 17, "./lib/lib_arcade_")) {
        err.flag = GameError::ERRPATH;
        throw err;
    }
    return spath;
}
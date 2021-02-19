/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** Storage.hpp
*/

#ifndef STORAGE_HPP
# define STORAGE_HPP

#include <string>
#include <vector>
#include <stdint.h>
#include <filesystem>

using namespace std;

static const char *const LIB_PATH         = "./lib/";
static const char *const GAME_PATH        = "./games/";
static const string     &DLIB_EXT         = ".so";
static const string     &LIB_FILEFORMAT   = "./lib/lib_arcade_";
static const string     &GAMES_FILEFORMAT = "./games/lib_arcade_";

class Storage
{
    public:
        Storage(const char *) noexcept;
        ~Storage() noexcept = default;
    public:
        const vector<string> &getNames() const noexcept;
    public:
        uint_fast32_t  index;
        vector<string> dlname;
    protected:
        vector<string> name;
};

class GameStorage: public Storage
{
    public:
        GameStorage() noexcept;
        ~GameStorage() noexcept = default;
};

class LibStorage: public Storage
{
    public:
        LibStorage() noexcept;
        ~LibStorage() noexcept = default;
};

#endif
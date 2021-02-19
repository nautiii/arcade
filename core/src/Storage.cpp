/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** Storage.cpp
*/

#include "Storage.hpp"

Storage::Storage(const char *path) noexcept
    : index(0)
{
    for (const auto &it : filesystem::directory_iterator(path)) {
        const std::string file = it.path().generic_string();
        if (file.compare(file.length() - 3, 3, DLIB_EXT) == 0)
            dlname.push_back(file);
    }
}

const vector<string> &Storage::getNames() const noexcept
{
    return name;
}

GameStorage::GameStorage() noexcept
    : Storage(GAME_PATH)
{
    for (const auto n : dlname)
        if (!n.compare(0, 19, GAMES_FILEFORMAT)) {
            string game = n.substr(19);
            game.resize(game.length() - 3);
            name.push_back(game);
        }
}

LibStorage::LibStorage() noexcept
    : Storage(LIB_PATH)
{
    for (const auto n : dlname)
        if (!n.compare(0, 17, LIB_FILEFORMAT)) {
            string lib = n.substr(17);
            lib.resize(lib.length() - 3);
            name.push_back(lib);
        }
}
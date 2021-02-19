/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** main.cpp
*/

#include "Core.hpp"

int main(int ac, const char **av)
{
    try {
        Core core(ac, *(++av));

        if (core.launchMenu() == arcade::Commands::QUIT)
            return 0;
        const int score = core.launchGame();
        core.saveScore(score);
    } catch (GameError &error) {
        return Core::sendErr(error);
    }
    return 0;
}
/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "IGraphics.hpp"
#include <list>
#include <chrono>

using namespace std::chrono;

namespace arcade
{
    class Nibbler : public IGame {
        public:
            Nibbler();
            ~Nibbler();
        public:
            vector<display_t> &getInitState() final;
            vector<display_t> &getState() final;
            display_t initNode(string path, string ascii, float x, float y);
            void move(char) final;
            void restart() final;
            void changePos(float x, float y);
            uint64_t getScore() final;
            bool floatTolerance(float a, float b, float ecart = 0.01f);
            arcade::statusGame &getStatus() final;
            void selfCol();
            bool speedGame() final;
        private:
            vector<display_t> initedMap;
            list<display_t> initedSnake;
            vector<display_t> returnMap;
            vector<display_t> map;
            list<display_t> snake;
            display_t fruit;
            vector<string> fruits;
            uint64_t score;
            arcade::statusGame status;
            steady_clock::time_point timer;
    };
}

#endif /* !NIBBLER_HPP_ */
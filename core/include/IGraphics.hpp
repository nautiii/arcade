/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** IGraphics.hpp
*/

#ifndef IGRAPHICS_HPP
# define IGRAPHICS_HPP

using namespace std;

#include <iostream>
#include <vector>

static const float FPS_60 = 0.0165;

typedef struct display_s
{
    string ascii;
    string foreground;
    string background;
    string image;
    float  x;
    float  y;
    bool   isPrint;
} display_t;

namespace arcade
{
    enum Commands
    {
        NONE      = -1,
        QUIT      = 0,
        NEW_NAME  = 110, // n
        PREV_LIB  = 97,  // a
        NEXT_LIB  = 101, // e
        PREV_GAME = 111, // o
        NEXT_GAME = 112, // p
        RESTART   = 114, // r
        MENU      = 109, // m
        ESCAPE    = 27,  // ESC
        UP        = 122, // z
        DOWN      = 115, // s
        LEFT      = 113, // q
        RIGHT     = 100, // d
        ENTER     = 10,  // enter
    };
    enum statusGame {
        INGAME,
        WIN,
        LOSE,
    };
    class IGraphics
    {
        public:
            virtual ~IGraphics() = default;
        public:
            virtual char getEvent(void) = 0;
            virtual void print(display_t &) = 0;
            virtual void destructor() = 0;
            virtual void refresh() = 0;
            virtual int  getWindowHeight() = 0;
            virtual int  getWindowWidth() = 0;
            virtual bool clockDisplay() = 0;
    };
    class IGame
    {
        public:
            virtual ~IGame() = default;
        public:
            virtual vector<display_t> &getInitState() = 0;
            virtual vector<display_t> &getState() = 0;
            virtual void move(char) = 0;
            virtual void restart() = 0;
            virtual uint64_t getScore() = 0;
            virtual arcade::statusGame &getStatus() = 0;
            virtual bool speedGame() = 0;
    };
}

#endif
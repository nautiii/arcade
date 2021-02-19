/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** IAaLib.hpp
*/

#ifndef IAALIB_HPP
# define IAALIB_HPP

#include <aalib.h>
#include "IGraphics.hpp"
#include <chrono>

using namespace std::chrono;

namespace arcade
{
    class IAaLib : public IGraphics
    {
        public:
            IAaLib();
            ~IAaLib() = default;

            char getEvent(void) final;
            void print(display_t &) final;
            void destructor() final;
            void refresh() final;
            int  getWindowHeight() final;
            int  getWindowWidth() final;
            bool clockDisplay() final;
        private:
            aa_context *context;
            steady_clock::time_point timer;
    };
}

#endif
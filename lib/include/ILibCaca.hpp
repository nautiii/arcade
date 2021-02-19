/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** ILibCaca.hpp
*/

#ifndef ILIBCACA_HPP
# define ILIBCACA_HPP

#include "caca.h"
#include "IGraphics.hpp"
#include <chrono>

using namespace std::chrono;

namespace arcade
{
    class ILibCaca: public IGraphics
    {
        public:
            ILibCaca();
            ~ILibCaca() = default;
        public:
            char getEvent(void) final;
            void print(display_t &) final;
            void destructor() final;
            void refresh() final;
            int  getWindowHeight() final;
            int  getWindowWidth() final;
            bool clockDisplay() final;
        private:
            caca_canvas_t  *window;
            caca_display_t *disp;
            caca_event_t    event;
            steady_clock::time_point timer;
    };
}

#endif
/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** ISfml.hpp
*/

#ifndef ISFML_HPP
# define ISFML_HPP

#include "IGraphics.hpp"
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define WINDOW_NAME "ARCADE"
#define ARCADE_FONT "./assets/std.otf"

using namespace sf;
using namespace std::chrono;

namespace arcade
{
    class ISfml : public IGraphics
    {
        public:
            ISfml();
            ~ISfml() = default;
        public:
            char getEvent(void) final;
            void print(display_t &) final;
            void destructor() final;
            void refresh() final;
            int  getWindowHeight() final;
            int  getWindowWidth() final;
            bool clockDisplay() final;
        private:
            RenderWindow window;
            Event        event;
            Font         font;
            steady_clock::time_point timer;
    };
}

#endif
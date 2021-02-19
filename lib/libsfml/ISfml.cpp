/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** ISfml.cpp
*/

#include "ISfml.hpp"

arcade::ISfml::ISfml()
    : timer(steady_clock::now())
{
    window.create(VideoMode(720, 480), WINDOW_NAME);
    font.loadFromFile(ARCADE_FONT);
}

char arcade::ISfml::getEvent(void)
{
    if (window.isOpen())
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                return Commands::QUIT;
            if (event.type == Event::KeyPressed && (event.key.code >= Keyboard::Key::Num0 && event.key.code <= Keyboard::Key::Num9))
                return (event.key.code + 22);
            if (event.type == Event::KeyPressed && (event.key.code >= Keyboard::Key::A && event.key.code <= Keyboard::Key::Z))
                return (event.key.code + 97);
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Key::Escape)
                return Commands::ESCAPE;
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Key::Return)
                return Commands::ENTER;
        }
    return Commands::NONE;
}

void arcade::ISfml::print(display_t &display)
{
    if (!window.isOpen() || !display.isPrint)
        return ;
    if (display.image.empty() == false) {
        Texture texture;
        if (texture.loadFromFile(display.image)) {
            Sprite sprite(texture);
            sprite.setPosition(display.x, display.y);
            window.draw(sprite);
        }
    } else if (!this->font.getInfo().family.empty()) {
        Text text(display.ascii, font, static_cast<int>(0.03 * getWindowHeight()));
        text.setPosition(display.x, display.y);
        window.draw(text);
    }
}

void arcade::ISfml::destructor()
{
    if (window.isOpen())
        window.close();
}

void arcade::ISfml::refresh()
{
    if (window.isOpen()) {
        window.display();
        window.clear();
    }
}

int arcade::ISfml::getWindowHeight()
{
    return window.getSize().y;
}

int arcade::ISfml::getWindowWidth()
{
    return window.getSize().x;
}

bool arcade::ISfml::clockDisplay()
{
    duration<double> time_span = duration_cast<duration<double>>(steady_clock::now() - timer);
    
    if (time_span.count() >= FPS_60) {
        timer = steady_clock::now();
        return true;
    }
    return false;
}

extern "C" arcade::IGraphics *create()
{
    return new arcade::ISfml();
}
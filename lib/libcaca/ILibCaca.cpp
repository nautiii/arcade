/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ILibCaca
*/

#include "ILibCaca.hpp"

arcade::ILibCaca::ILibCaca()
    : timer(steady_clock::now())
{
    this->window = caca_create_canvas(90, 30);
    this->disp = caca_create_display(this->window);
}

void arcade::ILibCaca::destructor()
{
    caca_free_canvas(this->window);
    caca_free_display(this->disp);
}

char arcade::ILibCaca::getEvent(void)
{
    caca_get_event(this->disp, CACA_EVENT_QUIT | CACA_EVENT_KEY_PRESS, &event, 1);
    if (caca_get_event_type(&event) == CACA_EVENT_QUIT)
        return arcade::Commands::QUIT;
    if (caca_get_event_type(&event) == CACA_EVENT_KEY_PRESS) {
        int ev = caca_get_event_key_ch(&event);
        return (ev == 13) ? arcade::Commands::ENTER : ev;
    }
    return arcade::Commands::NONE;
}

void arcade::ILibCaca::refresh()
{
    caca_refresh_display(this->disp);
}

void arcade::ILibCaca::print(display_t &display)
{
    caca_printf(this->window, display.x, display.y, display.ascii.c_str());
}

int arcade::ILibCaca::getWindowHeight()
{
    return caca_get_canvas_height(this->window);
}

int arcade::ILibCaca::getWindowWidth()
{
    return caca_get_canvas_width(this->window);
}

bool arcade::ILibCaca::clockDisplay()
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
    return new arcade::ILibCaca();
}
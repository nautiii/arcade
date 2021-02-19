/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IAaLib
*/

#include <aalib.h>
#include "IAaLib.hpp"

arcade::IAaLib::IAaLib()
    : timer(steady_clock::now())
{
    aa_defparams.recheight = 37;
    aa_defparams.recwidth = 90;
    aa_defparams.height = 37;
    aa_defparams.width = 90;
    context = aa_autoinit(&aa_defparams);
    if (context == NULL)
        throw "initialization of aa-lib went wrong.";
    if (aa_autoinitkbd(context, 0) == 0)
        throw "initialization of aa-lib keyboard went wrong.";
    aa_hidecursor(context);
}

void arcade::IAaLib::destructor()
{
    aa_close(context);
}

char arcade::IAaLib::getEvent(void)
{
    int event = aa_getevent(context, 0);

    if (event == AA_NONE)
       return arcade::Commands::NONE;
    if (event == 13)
        return arcade::Commands::ENTER;
    return event;
}

void arcade::IAaLib::print(display_t &display)
{
    aa_puts(context, display.x, display.y, AA_BOLD, display.ascii.c_str());
}

void arcade::IAaLib::refresh()
{
    aa_flush(context);
}

int arcade::IAaLib::getWindowHeight()
{
    return aa_scrheight(context);
}

int arcade::IAaLib::getWindowWidth()
{
    return aa_scrwidth(context);
}

bool arcade::IAaLib::clockDisplay()
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
    try {
        return new arcade::IAaLib();
    } catch (const char *err) {
        cout << err << endl;
        return nullptr;
    }
}
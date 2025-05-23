#include "Timer.h"
#include "Game_Stat.h"

Timer::Timer()
{
    start_tick = 0;
    paused_tick = 0;

    is_paused = false;
    is_started = false;

    Store_pause = 0;
}

Timer::~Timer()
{

}

void Timer::start()
{
    is_started = true;
    is_paused = false;
    start_tick = SDL_GetTicks();
}

void Timer::stop()
{
    is_started = false;
    is_paused = false;
}

void Timer::paused()
{
    if (is_started)
    {
        is_paused = true;
        paused_tick = SDL_GetTicks() - start_tick;
    }
}

void Timer::unpaused()
{
    if (is_paused)
    {
        is_paused = false;
        start_tick = SDL_GetTicks();
        Store_pause+=paused_tick;
        paused_tick = 0;
    }
}

int Timer::get_tick()
{
    if (is_started)
    {
        if (is_paused)
        {
            return paused_tick;
        }
        else
        {
            return SDL_GetTicks() - start_tick;
        }
    }
    return 0;
}

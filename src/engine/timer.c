#include "timer.h"

static uint32_t ticks = 0;
static uint32_t seconds = 0;

void timer_init(void)
{
    timer_reset();
}

void timer_tick(void)
{
    ticks++;

    if (ticks % 60 == 0)
    {
        seconds++;
    }
}

uint32_t timer_get_ticks(void)
{
    return ticks;
}

uint32_t timer_get_seconds(void)
{
    return seconds;
}

void timer_reset(void)
{
    ticks = 0;
    seconds = 0;
}

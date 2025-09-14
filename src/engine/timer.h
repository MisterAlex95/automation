#ifndef TIMER_H
#define TIMER_H

#include <gb/gb.h>
#include <stdint.h>

void timer_init(void);
void timer_tick(void);

uint32_t timer_get_ticks(void);
uint32_t timer_get_seconds(void);

void timer_reset(void);

#endif // TIMER_H

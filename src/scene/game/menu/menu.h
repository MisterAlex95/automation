#ifndef MENU_H
#define MENU_H

typedef enum
{
    MENU_NONE,
    MENU_TILE_SELECTION,
    MENU_ORIENTATION_SELECTION
} MenuState;

void menu_show_tile_selection(void);
void menu_show_orientation_selection(void);
void menu_clear(void);

#endif // MENU_H
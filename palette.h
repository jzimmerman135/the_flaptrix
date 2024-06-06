#ifndef PALETTE_H
#define PALETTE_H

#include "raylib.h"

#define N_BACKGROUND_PALETTES 5

enum {
    COLOR_BACKGROUND,
    COLOR_AVATAR,
    COLOR_AVATAR_BORDER1,
    COLOR_AVATAR_BORDER2,
    COLOR_TUBE_DEFAULT,
    COLOR_TUBE_SHADOW,
    COLOR_TUBE_DEATH,
    COLOR_TUBE_PLATFORM,
    COLOR_TUBE_TOGGLE,
    COLOR_TUBE_BLUE,
    COLOR_TUBE_RED,
    COLOR_TUBE_WINNER1,
    COLOR_TUBE_WINNER2,
};

extern const Color background_palette[N_BACKGROUND_PALETTES];
Color get_color(int clr);

#endif

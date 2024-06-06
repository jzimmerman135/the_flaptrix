#include "palette.h"

const Color background_palette[N_BACKGROUND_PALETTES] = {
    CLITERAL(Color){0xFF, 0xFF, 0xBA, 0xFF},
    CLITERAL(Color){0xFF, 0xDD, 0xFF, 0xFF},
    CLITERAL(Color){0xDD, 0xDD, 0xFF, 0xFF},
};

const Color palette[] = {
    /* COLOR_BACKGROUND */
    CLITERAL(Color){0xFF, 0xFF, 0xBA, 0xFF},
    /* COLOR_AVATAR */
    CLITERAL(Color){0xBA, 0xE1, 0xFF, 0xFF},
    /* COLOR_AVATAR_BORDER1 */
    CLITERAL(Color){0xFF, 0xFF, 0xFF, 0xFF},
    /* COLOR_AVATAR_BORDER2 */
    CLITERAL(Color){0x92, 0x92, 0x92, 0xFF},
    /* COLOR_TUBE_DEFAULT */
    CLITERAL(Color){0xff, 0xb3, 0xba, 0xFF},
    /* COLOR_TUBE_SHADOW */
    CLITERAL(Color){0x00, 0x00, 0x00, 0x20},
    /* COLOR_TUBE_DEATH*/
    CLITERAL(Color){0xC9, 0xC9, 0xC9, 0xFF},
    /* COLOR_TUBE_PLATFORM */
    CLITERAL(Color){0xff, 0xb3, 0xba, 0xFF},
    /* COLOR_TUBE_TOGGLE */
    CLITERAL(Color){0xBA, 0xFF, 0xC9, 0xFF},
    /* COLOR_TUBE_BLUE */
    CLITERAL(Color){0xBA, 0xE1, 0xFF, 0xFF},
    /* COLOR_TUBE_RED */
    CLITERAL(Color){0xDB, 0xDC, 0xFF, 0xFF},
    /* COLOR_TUBE_WINNER1 */
    CLITERAL(Color){0xFD, 0xB5, 0x15, 0xFF},
    /* COLOR_TUBE_WINNER2 */
    CLITERAL(Color){0xFF, 0xEF, 0x00, 0xFF},
};

Color get_color(int clr) {
    return palette[clr];
}

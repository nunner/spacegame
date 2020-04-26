#pragma once

#define INIT_LINES 30
#define INIT_COLS 140

#define LOCATION_COUNT 10

#define C(x)		COLOR_PAIR(x)
#define C_SELECTED 	C(1)
#define C_VISITED	C(2)

#include <ncurses.h>
#include "types.h"

void
enter_sector(sector_t *sector);

location_t
map();

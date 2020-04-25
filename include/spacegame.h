#pragma once

#define LOCATION_COUNT 10

#define C(x)		COLOR_PAIR(x)
#define C_SELECTED 	C(1)

#include <ncurses.h>
#include "types.h"

void
map();

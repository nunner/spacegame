#pragma once

#define DEBUG

#define INIT_LINES 30
#define INIT_COLS 140

#define LOCATION_COUNT 10

#define C(x)			COLOR_PAIR(x)
#define C_A_SELECTED	C(1)
#define C_A_VISITED		C(2)
#define C_A_CURRENT		C(3)
#define C_RED			4
#define C_YELLOW 		5	
#define C_GREEN			6
#define C_TRANS 		7
#define C_DEFAULT		8

#include <ncurses.h>
#include "types.h"

void
start_game();

void
enter_sector(sector_t *sector);

void
map();

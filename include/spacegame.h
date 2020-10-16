#pragma once

#define DEBUG

#define INIT_LINES 30
#define INIT_COLS 140

#define LOCATION_COUNT 22

#define C_BAR_RED 		1
#define C_BAR_YELLOW 	2
#define C_BAR_GREEN		3
#define C_BAR_TRANS 	4

#define C_RED			5
#define C_YELLOW		6	
#define C_GREEN		 	7
#define C_CYAN			8
#define C_BLUE			9
#define C_DEFAULT 		10

#define C_SELECTED		C_DEFAULT + 1
#define C_DISABLED		C_SELECTED + 1

#include <ncurses.h>
#include "types.h"

void
start_game();

void
map();

void
crew();

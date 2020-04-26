#pragma once

#include "types.h"

#include <ncurses.h>

typedef struct {
	char *name;
	bool property;
	WINDOW *window;
} crewwindow_t;

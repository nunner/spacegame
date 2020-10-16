#pragma once

#include <ncurses.h>

#define CONTROL_WIDTH 40

void
check_state();

void
print_health(WINDOW *w);

void
print_status(WINDOW *w, int y, int x, char *name, bool status);

void
print_energy(WINDOW *w, int y, int x, int value);

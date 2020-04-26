#pragma once

#include <ncurses.h>

#define CONTROL_WIDTH 40

typedef struct {
	void (*left)();
	void (*right)();
	void (*up)();
	void (*down)();
	void (*enter)();
} statewindow;

statewindow *
state_peaceful(WINDOW *w);

statewindow *
state_trade(WINDOW *w);

statewindow *
state_attack(WINDOW *w);

void
print_health(WINDOW *w);

void
print_status(WINDOW *w, int y, int x, char *name, bool status);

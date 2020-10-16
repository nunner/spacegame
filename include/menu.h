#pragma once

#include <ncurses.h>
#include <stdlib.h>

typedef struct {
	char *name;
	char *code;
	void *ptr;
	bool enabled;
} ITEM;

typedef struct {
	ITEM *items;
	size_t item_count;
	int index;
	uint32_t x;
	uint32_t y;
	WINDOW *w;
} MENU;

typedef enum {
	MENU_UP,
	MENU_DOWN,
	MENU_SELECT
} MENU_ACTION;

MENU *
create_menu(ITEM *items, size_t count);

ITEM
create_item(char *name, char *code, bool enabled);

void
post_menu(MENU *m, WINDOW *w, int x, int y);

ITEM *
menu_driver(MENU *m, MENU_ACTION action);

void
change_state(MENU *m, char *code, bool value);

#include "menu.h"
#include "spacegame.h"

#include <stdlib.h>
#include <string.h>

void draw(MENU *m);

MENU *
create_menu(ITEM *items, size_t count)
{
	MENU *menu = malloc(sizeof(MENU));	
	menu->items = items;
	menu->item_count = count;
	menu->index = 0;

	return menu;
}

ITEM 
create_item(char *name, char *code, bool enabled)
{
	ITEM *item = malloc(sizeof(ITEM));
	item->name = name;
	item->code = code;
	item->enabled = enabled;
	return *item;
}

void
post_menu(MENU *m, WINDOW *w, int x, int y)
{
	m->x = x;
	m->y = y;
	m->w = w;

	draw(m);
}

void
draw(MENU *m)
{
	for(size_t i = 0; i < m->item_count; i++) {
		if(i == m->index)
			wcolor_set(m->w, C_SELECTED, 0);
		if(!m->items[i].enabled)
			wcolor_set(m->w, C_DISABLED, 0);

		mvwprintw(m->w, m->y+i, m->x, " %s ", m->items[i].name);

		wcolor_set(m->w, COLOR_BLACK, 0);
	}
	wrefresh(m->w);
}

uint32_t find_lower(MENU *m);
uint32_t find_upper(MENU *m);

ITEM *
menu_driver(MENU *m, MENU_ACTION action)
{
	switch(action)
	{
		case MENU_UP: 
			if(m->index > 0 && find_lower(m) != -1)
				m->index = find_lower(m);
			break;
		case MENU_DOWN: 
			if(m->index < m->item_count - 1 && find_upper(m) != -1)
				m->index = find_upper(m);
			break;
		case MENU_SELECT:
			if(m->items[m->index].enabled) return &m->items[m->index];
	}
	draw(m);
	return 0;
}

void
change_state(MENU *m, char *code, bool value)
{
	for(size_t i = 0; i < m->item_count; i++)
	{
		if(strcmp(code, m->items[i].code) == 0) {
			m->items[i].enabled = value;

			while(m->index < m->item_count && !m->items[m->index].enabled)
				m->index++;

			break;
		}
	}
	draw(m);
}

uint32_t 
find_lower(MENU *m) {
	int index;
	
	for(index = m->index - 1; index >= 0; index--) {
		if(m->items[index].enabled) return index;
	}

	return -1;
}

uint32_t find_upper(MENU *m) {
	int index;
	
	for(index = m->index + 1; index < m->item_count; index++) {
		if(m->items[index].enabled) return index;
	}

	return -1;
}

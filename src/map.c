#include "spacegame.h"
#include "ship.h"

#include "stdlib.h"
#include <string.h>

#define PLANET_CHAR 'o'
#define STAR_CHAR 	'*'

extern WINDOW *mainwindow;
extern gamestate_t *state;

static WINDOW *mapwin;

static int pos;

void
map()
{
	mapwin = dupwin(mainwindow);
	box(mapwin, 0, 0);
	keypad(mapwin, true);

	pos = 0;

	int direction = 0;

	int location_index = 0;
	for(int i = 0; i < LOCATION_COUNT; i++)
	{
		if(state->current_sector->locations[i].x == state->current_location->x && state->current_sector->locations[i].y == state->current_location->y) {
			pos = location_index = i;
			break;
		}
	}

	while(1) {
		mvwprintw(mapwin, 0, (INIT_COLS-strlen("Sector map"))/2, "Sector map");

		for(int i = 0; i < LOCATION_COUNT; i++)
		{
			location_t location = state->current_sector->locations[i];
			
			if(i == pos) {
				if(i == location_index) {
					wattron(mapwin, C_A_CURRENT);
					mvwprintw(mapwin, location.y, location.x-1, ">%c<", PLANET_CHAR);
					wattroff(mapwin, C_A_CURRENT);
				} else  {
					wattron(mapwin, C_A_SELECTED);
					mvwprintw(mapwin, location.y, location.x-1, "(%c)", PLANET_CHAR);
					wattroff(mapwin, C_A_SELECTED);
				}
			} else if(i == location_index){
				mvwprintw(mapwin, location.y, location.x-1, ">%c<", PLANET_CHAR);
			} else if(location.visited) {
				wattron(mapwin, C_A_VISITED);
				mvwprintw(mapwin, location.y, location.x-1, " %c ", PLANET_CHAR);
				wattroff(mapwin, C_A_VISITED);
			}
			else mvwprintw(mapwin, location.y, location.x-1, " %c ", PLANET_CHAR);
		}


		switch((direction = wgetch(mapwin)))
		{
			// Left
			case KEY_LEFT:
			case 'h':
				if(pos > 0) pos--;
				break;
			// Right
			case KEY_RIGHT:
			case 'l':
				if(pos < LOCATION_COUNT - 1) pos++;
				break;
			// Enter
			case 10:
				if(pos != location_index) {
					write_to_screen("Switched to new Sector.\n", SYSTEM);
					state->current_location = &state->current_sector->locations[pos];
				}
				goto end;
			// Esc
			case 27:
				goto end;
		}

	}

end:
	delwin(mapwin);
	return;
}

#include "spacegame.h"
#include "ship.h"

#include "stdlib.h"
#include <string.h>

#define PLANET_CHAR 'o'
#define STAR_CHAR 	'*'

extern WINDOW *mainwindow;
extern gamestate_t *state;

location_t *current_destination;

static WINDOW *mapwin;


void
switch_location()
{
	state->current_location->visited = true;
	state->current_location = current_destination;
	write_to_screen("Setting course for new location\n", M_SYSTEM);
	write_to_screen("Arrived at location\n", M_SYSTEM);
	current_destination = 0;
}

void
map()
{
	mapwin = dupwin(mainwindow);
	box(mapwin, 0, 0);
	keypad(mapwin, true);

	int pos = state->current_location->index;
	int direction = 0;

	while(1) {
		mvwprintw(mapwin, 0, (INIT_COLS-strlen("Sector map"))/2, "Sector map");

		for(int i = 0; i < LOCATION_COUNT; i++)
		{
			location_t location = state->current_sector->locations[i];
			
			if(i == pos) {
				if(i == state->current_location->index) {
					wcolor_set(mapwin, C_CYAN, 0);
					mvwprintw(mapwin, location.y, location.x-1, ">%c<", PLANET_CHAR);
				} else  {
					wcolor_set(mapwin, C_YELLOW, 0);
					mvwprintw(mapwin, location.y, location.x-1, "(%c)", PLANET_CHAR);
				}
			} else if(i == state->current_location->index){
				wcolor_set(mapwin, C_BLUE, 0);
				mvwprintw(mapwin, location.y, location.x-1, ">%c<", PLANET_CHAR);
			} else if(location.visited) {
				wcolor_set(mapwin, C_GREEN, 0);
				mvwprintw(mapwin, location.y, location.x-1, " %c ", PLANET_CHAR);
			} 
			else mvwprintw(mapwin, location.y, location.x-1, " %c ", PLANET_CHAR);

			wcolor_set(mapwin, C_DEFAULT, 0);
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
				if(pos != state->current_location->index) {
					write_to_screen("Destination set.\n", M_SYSTEM);
					current_destination = &state->current_sector->locations[pos];
				}
				goto end;
			// Esc
			case ' ':
				goto end;
		}

	}

end:
	delwin(mapwin);
	return;
}

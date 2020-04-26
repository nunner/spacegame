#include "spacegame.h"
#include "map.h"

#include "stdlib.h"

#define PLANET_CHAR "o"
#define STAR_CHAR 	"*"

extern WINDOW *mainwindow;

static int max_x, max_y;
static WINDOW *mapwin;
static WINDOW *textwin;

static int index;

void
fill_positions(sector_t *sector)
{
	for(int i = 0; i < LOCATION_COUNT; i++)
	{
		sector->locations[i].x = rand() % max_x;
		sector->locations[i].y = rand() % max_y;
		sector->locations[i].visited = true;
	}
}

location_t
map()
{
	mapwin = dupwin(mainwindow);
	box(mapwin, 0, 0);
	textwin = subwin(mapwin, INIT_LINES, 30, 0, INIT_COLS-30);
	getmaxyx(mapwin, max_y, max_x);

	index = 0;

	sector_t *sect = (sector_t *) malloc(sizeof(sector_t));
	fill_positions(sect);

	int direction = 0;

	while(1) {
		for(int i = 0; i < LOCATION_COUNT; i++)
		{
			location_t location = sect->locations[i];
			if(index == i) {
				wattron(mapwin, C_SELECTED);
				mvwprintw(mapwin, location.y, location.x, PLANET_CHAR);
				wattroff(mapwin, C_SELECTED);
			} else if(location.visited) {
				wattron(mapwin, C_VISITED);
				mvwprintw(mapwin, location.y, location.x, PLANET_CHAR);
				wattroff(mapwin, C_VISITED);
			}
			else mvwprintw(mapwin, location.y, location.x, PLANET_CHAR);
		}

		wrefresh(mapwin);

		switch((direction = wgetch(mapwin)))
		{
			// Left
			case 68:
			case 'h':
				if(index > 0) index--;
				break;
			// Right
			case 67:
			case 'l':
				if(index < LOCATION_COUNT - 1) index++;
				break;
			// Enter
			case 10:
				goto end;
		}
	}

end:
	delwin(textwin);
	delwin(mapwin);
	return sect->locations[index];
}

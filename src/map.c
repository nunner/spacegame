#include "spacegame.h"
#include "map.h"

#include "stdlib.h"

#define PLANET_CHAR "o"
#define STAR_CHAR 	"*"

extern WINDOW *mainwindow;

static int max_x, max_y;
static WINDOW *window;

static int index;

void
fill_positions(sector_t *sector)
{
	for(int i = 0; i < LOCATION_COUNT; i++)
	{
		sector->locations[i].x = rand() % max_x;
		sector->locations[i].y = rand() % max_y;
	}
}

void
map()
{
	window = dupwin(mainwindow);
	getmaxyx(window, max_y, max_x);

	index = 0;

	sector_t *sect = (sector_t *) malloc(sizeof(sector_t));
	fill_positions(sect);

	int direction = 0;

	while(1) {
		for(int i = 0; i < LOCATION_COUNT; i++)
		{
			location_t location = sect->locations[i];
			if(index == i) {
				wattron(window, C_SELECTED);
				mvwprintw(window, location.y, location.x, PLANET_CHAR);
				wattroff(window, C_SELECTED);
			} 
			else mvwprintw(window, location.y, location.x, PLANET_CHAR);
		}

		wrefresh(window);

		switch((direction = wgetch(window)))
		{
			case 68:
			case 'h':
				if(index > 0) index--;
				break;
			case 67:
			case 'l':
				if(index < LOCATION_COUNT - 1) index++;
				break;
		}
	}
}

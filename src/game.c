#include "spacegame.h"
#include "types.h"

#include "ship.h"

#include <stdlib.h>

extern WINDOW *mainwindow;

ship_t *player;
sector_t *current_sector;
location_t *current_location;

static sector_t *initial_sector;
static int max_x, max_y;

sector_t *
create_sector();

ship_t *
create_ship();

void
start_game()
{
	getmaxyx(mainwindow, max_y, max_x);

	player = create_ship();
	initial_sector = create_sector();

	current_sector = initial_sector;
	current_location = &current_sector->locations[0];
	current_location->visited = true;

	while(player->health != 0)
	{
		show_gui();
	}
}

ship_t *
create_ship()
{
	ship_t *ship = malloc(sizeof(ship_t));
	ship->controls = malloc(sizeof(controls_t));

	ship->energy = 0;
	ship->maxenergy = 15;

	return ship;
}

sector_t *
create_sector()
{
	sector_t *sector = malloc(sizeof(sector_t));

	for(int i = 0; i < LOCATION_COUNT; i++)
	{
		sector->locations[i].x = rand() % max_x;
		sector->locations[i].y = rand() % max_y;
		sector->locations[i].visited = true;
	}

	return sector;
}

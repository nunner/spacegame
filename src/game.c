#include "spacegame.h"
#include "types.h"

#include "ship.h"

#include <stdlib.h>
#include <string.h>

extern WINDOW *mainwindow;

gamestate_t *state;

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

	state = malloc(sizeof(gamestate_t));
	memset(state, 0, sizeof(gamestate_t));

	state->player = create_ship();
	initial_sector = create_sector();

	state->current_sector = initial_sector;
	state->current_location = &state->current_sector->locations[0];
	state->current_location->visited = true;

	state->current_state = PEACE;

	while(state->player->health != 0)
	{
		show_gui();
	}
}

ship_t *
create_ship()
{
	ship_t *ship = malloc(sizeof(ship_t));
	ship->controls = malloc(sizeof(controls_t));
	ship->status = malloc(sizeof(status_t));

	ship->health = 100;
	ship->energy = 0;
	ship->maxenergy = 15;

	ship->status->machine_deck = true;
	ship->status->phaser_deck = false;
	ship->status->engine_decks = true;
	ship->status->oxygen = true;

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

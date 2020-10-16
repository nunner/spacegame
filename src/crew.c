#include "spacegame.h"
#include "crew.h"
#include "state.h"
#include "menu.h"

#include <stdlib.h>
#include <string.h>

#define WIDTH INIT_COLS/4

enum {
	PHASER,
	BOOSTER,
};

extern WINDOW *mainwindow;
extern gamestate_t *state;

extern location_t *current_destination;

void (*functions[])() = {
	[BOOSTER] = switch_location,
};

static WINDOW *crewwin;

static WINDOW *overview;
static WINDOW *machinewin;
static WINDOW *phaserwin;
static WINDOW *enginewin;

static MENU *menu;

void
create_crewwindow(WINDOW *w, char *name, bool property, int energy)
{
	box(w, 0, 0);
	mvwprintw(w, 0, (WIDTH-strlen(name))/2, name);
	print_energy(w, 2, 2, energy);
	print_status(w, 4, 2, "Status", property);
	wrefresh(w);
}

void
draw_machine()
{
	create_crewwindow(machinewin, "Machine", state->player->status.machine_deck, state->player->controls.shield);
}

void
draw_phaser()
{
	create_crewwindow(phaserwin, "Phaser", state->player->status.phaser_deck, state->player->controls.phasers);

	change_state(menu, PHASER, false);
}

void
draw_engine()
{
	create_crewwindow(enginewin, "Engine", state->player->status.engine_deck, state->player->controls.booster);

	change_state(menu, BOOSTER, false);

	if(current_destination != 0) {
		int distance = abs(state->current_location->index - current_destination->index);

		wcolor_set(enginewin, C_CYAN, 0);

		mvwprintw(enginewin, 8, 2, "[Destination set]");
		mvwprintw(enginewin, 10, 2, "Distance: %d", distance);

		if(state->player->controls.booster >= distance) {
			wcolor_set(enginewin, C_GREEN, 0);
			mvwprintw(enginewin, 12, 2, "Sufficient energy supplied");
			change_state(menu, BOOSTER, true);
		} else {
			wcolor_set(enginewin, C_RED, 0);
			mvwprintw(enginewin, 12, 2, "Insufficient energy supplied");
			change_state(menu, BOOSTER, false);
		}

		wcolor_set(enginewin, C_DEFAULT, 0);
	}
}

void
crew()
{
	crewwin = dupwin(mainwindow);

	overview = subwin(crewwin,   INIT_LINES, WIDTH, 0, 0);
	machinewin = subwin(crewwin, INIT_LINES, WIDTH, 0, WIDTH);
	phaserwin = subwin(crewwin,  INIT_LINES, WIDTH, 0, WIDTH*2);
	enginewin = subwin(crewwin,  INIT_LINES, WIDTH, 0, WIDTH*3);

	box(overview, 0, 0);
	keypad(crewwin, true);

	char *options[] = {
		[PHASER] = "Fire phasers", 		
		[BOOSTER] = "Activate boosters",
	};

	int len = 2;
	ITEM *items = malloc(len * sizeof(ITEM) );

	for(size_t i = 0; i < len; i++) {
		items[i] = create_item(options[i], i, true);	
	}
	
	menu = create_menu(items, len);
	post_menu(menu, overview, 2, 2);

	draw_machine();	
	draw_phaser();
	draw_engine();

	while(1) {
		int key = 0;
		switch((key = wgetch(crewwin)))
		{
			case KEY_UP:
				menu_driver(menu, MENU_UP);
				break;
			case KEY_DOWN:
				menu_driver(menu, MENU_DOWN);
				break;
			// Return
			case 10: {
				ITEM *funct = menu_driver(menu, MENU_SELECT);
				functions[funct->val]();
				goto end;
			}
			// Escape
			case ' ':
				goto end;
		}

	}

end:
	return;
}

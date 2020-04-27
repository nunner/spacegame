#include "spacegame.h"
#include "crew.h"
#include "state.h"

#include "stdlib.h"
#include <string.h>

#define WIDTH INIT_COLS/4

extern WINDOW *mainwindow;
extern gamestate_t *state;

extern location_t *current_destination;

static WINDOW *crewwin;

static WINDOW *overview;
static WINDOW *machinewin;
static WINDOW *phaserwin;
static WINDOW *enginewin;

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
	create_crewwindow(machinewin, "Machine", state->player->status->machine_deck, state->player->controls->shield);

	if(current_destination != 0) {
		int distance = abs(state->current_location->index - current_destination->index);

		mvwprintw(machinewin, 8, 2, "[Destination set]");
		mvwprintw(machinewin, 10, 2, "Distance: %d", distance);

		wcolor_set(machinewin, COLOR_BLACK, 0);
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

	while(1) {
		draw_machine();	

		int key = 0;
		switch((key = wgetch(crewwin)))
		{
			// Escape
			case 27:
				goto end;
		}

	}

end:
	delwin(crewwin);
	return;
}

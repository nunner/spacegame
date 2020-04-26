#include "spacegame.h"
#include "crew.h"

#include "stdlib.h"
#include <string.h>

#define WIDTH INIT_COLS/4

extern WINDOW *mainwindow;
extern gamestate_t *state;

static WINDOW *crewwin;

static WINDOW *overview;
static WINDOW *machinewin;
static WINDOW *phaserwin;
static WINDOW *enginewin;

void
create_crewwindow(crewwindow_t *win)
{
	mvwprintw(win->window, 0, (INIT_COLS-strlen(win->name))/2, win->name);
	box(win->window, 0, 0);
	wrefresh(win->window);
}

void
crew()
{
	crewwindow_t windows[] = {
		{"Machine deck", state->player->status->machine_deck, machinewin},
		{"Phaser deck", state->player->status->phaser_deck, phaserwin},
		{"Engine deck", state->player->status->engine_deck, enginewin}
	};

	crewwin = dupwin(mainwindow);

	overview = subwin(crewwin,   INIT_LINES, WIDTH, 0, 0);
	machinewin = subwin(crewwin, INIT_LINES, WIDTH, 0, WIDTH);
	phaserwin = subwin(crewwin,  INIT_LINES, WIDTH, 0, WIDTH*2);
	enginewin = subwin(crewwin,  INIT_LINES, WIDTH, 0, WIDTH*3);

	box(overview, 0, 0);
	keypad(crewwin, true);

	while(1) {

		for(int i = 0; i < 3; i++) 	{
			create_crewwindow(&windows[i]);
		}

		wrefresh(overview);

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

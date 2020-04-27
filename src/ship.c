#include "spacegame.h"
#include "state.h"

#include <string.h>


extern WINDOW *mainwindow;
extern gamestate_t *state;

static statewindow *statewin_bindings;

static WINDOW *guiwin;

static WINDOW *controlwin;
static WINDOW *screenwin;
static WINDOW *text;
static WINDOW *statuswin;

static WINDOW *shieldwin;
static WINDOW *phaserwin;
static WINDOW *boosterwin;

void
print_control_bar(WINDOW *w, int value)
{
	for(int i = 0; i < 15; i++)
	{
		if(i >= value) wcolor_set(w, C_TRANS, 0);
		else if(i == 0) wcolor_set(w, C_RED, 0);
		else if(i == 5) wcolor_set(w, C_YELLOW, 0);
		else if(i == 10) wcolor_set(w, C_GREEN, 0);

		mvwprintw(w, 1, 1+i*2, "  ");
	}
	wrefresh(w);
	wcolor_set(w, COLOR_BLACK, 0);
}



void
draw_controls()
{
	mvwprintw(controlwin, 0, (CONTROL_WIDTH-strlen("Controls"))/2, "Controls");
	mvwprintw(controlwin, 1, 1, "Energy available: %02d/%02d", state->player->maxenergy-state->player->energy, state->player->maxenergy);

	// Controls for shield
	mvwprintw(controlwin, 3, (CONTROL_WIDTH-strlen("Shield"))/2, "Shield");
	mvwprintw(controlwin, 4, 2, "1");
	mvwprintw(controlwin, 4, CONTROL_WIDTH-3, "2");

	print_control_bar(shieldwin, state->player->controls->shield);

	// Controls for phaser
	mvwprintw(controlwin, 8, (CONTROL_WIDTH-strlen("Phasers"))/2, "Phasers");
	mvwprintw(controlwin, 9, 2, "3");
	mvwprintw(controlwin, 9, CONTROL_WIDTH-3, "4");

	print_control_bar(phaserwin, state->player->controls->phasers);

	// Controls for boosters
	mvwprintw(controlwin, 13, (CONTROL_WIDTH-strlen("Boosters"))/2, "Boosters");
	mvwprintw(controlwin, 14, 2, "5");
	mvwprintw(controlwin, 14, CONTROL_WIDTH-3, "6");

	print_control_bar(boosterwin, state->player->controls->booster);

	// Print status stuff
	print_status(controlwin, 20, 3, "Machine deck", state->player->status->machine_deck);
	print_status(controlwin, 22, 3, "Phaser deck", state->player->status->phaser_deck);
	print_status(controlwin, 24, 3, "Engine deck", state->player->status->engine_deck);

	wrefresh(controlwin);
}

void
draw_screen()
{
	mvwprintw(screenwin, 0, (INIT_COLS-CONTROL_WIDTH*2-strlen("Screen"))/2, "Screen");
	wrefresh(screenwin);
}

void
draw_status()
{
	switch(state->current_state) {
		case PEACE:
			statewin_bindings = state_peaceful(statuswin);
			break;
		case TRADE:
			statewin_bindings = state_trade(statuswin);
			break;
		case ATTACK:
			statewin_bindings = state_attack(statuswin);
			break;
	}
}

void
init()
{
	keypad(guiwin, true);
	scrollok(screenwin, true);

	box(controlwin, 0, 0);
	box(statuswin, 0, 0);
	box(screenwin, 0, 0);

	box(shieldwin, 0, 0);
	box(phaserwin, 0, 0);
	box(boosterwin, 0, 0);
}

void
write_to_screen(char *s, MESSAGE m)
{
	char *prefix;
	switch(m)
	{
		default:
		case SYSTEM:
			wcolor_set(text, COLOR_GREEN, 0);
			prefix = "[SHIP COMPUTER]";
			break;
		case STATUS:
			wcolor_set(text, COLOR_BLUE, 0);
			prefix = "[STATUS]";
			break;
		case TRADER:
			wcolor_set(text, COLOR_CYAN, 0);
			prefix = "[TRADER]";
			break;
		case ATTACKER:
			wcolor_set(text, COLOR_RED, 0);
			prefix = "[ATTACK]";
			break;
		case UNKNOWN:
			wcolor_set(text, COLOR_YELLOW, 0);
			prefix = "[UNKNOWN SHIP]";
			break;
	}

	wprintw(text, "%s %s", prefix, s);
	wrefresh(text);

	wcolor_set(screenwin, COLOR_BLACK, 0);
}

void
show_gui()
{
	guiwin = dupwin(mainwindow);

	controlwin = subwin(guiwin, INIT_LINES, CONTROL_WIDTH, 0, 0);
	shieldwin = subwin(controlwin, 3, CONTROL_WIDTH-8, 3, 4);
	phaserwin = subwin(controlwin, 3, CONTROL_WIDTH-8, 8, 4);
	boosterwin = subwin(controlwin, 3, CONTROL_WIDTH-8, 13, 4);

	statuswin = subwin(guiwin, INIT_LINES, CONTROL_WIDTH, 0, INIT_COLS-CONTROL_WIDTH);
	screenwin = subwin(guiwin, INIT_LINES, INIT_COLS-CONTROL_WIDTH*2, 0, CONTROL_WIDTH);
	text = derwin(screenwin, INIT_LINES-2, INIT_COLS-CONTROL_WIDTH*2-2, 1, 1);

	init();

	int key = 0;

	while(state->player->health != 0)
	{
		draw_controls();	
		draw_screen();
		draw_status();

		switch((key = wgetch(guiwin))) 
		{
			case 'M':
			case 'm':
				map();
				init();
				break;
			case 'C':
			case 'c':
				crew();
				init();
				break;
			case '1':
				if(state->player->controls->shield > 0) {
					state->player->controls->shield--;
					state->player->energy--;
				}
				break;
			case '2':
				if(state->player->controls->shield < 15 && state->player->energy < state->player->maxenergy) {
					state->player->controls->shield++;
					state->player->energy++;
				}
				break;
			case '3':
				if(state->player->controls->phasers > 0) {
					state->player->controls->phasers--;
					state->player->energy--;
				}
				break;
			case '4':
				if(state->player->controls->phasers < 15 && state->player->energy < state->player->maxenergy) {
					state->player->controls->phasers++;
					state->player->energy++;
				}
				break;
			case '5':
				if(state->player->controls->booster > 0) {
					state->player->controls->booster--;
					state->player->energy--;
				}
				break;
			case '6':
				if(state->player->controls->booster < 15 && state->player->energy < state->player->maxenergy) {
					state->player->controls->booster++;
					state->player->energy++;
				}
				break;
		}
	}

	delwin(shieldwin);
	delwin(phaserwin);
	delwin(boosterwin);
	delwin(screenwin);
	delwin(statuswin);
	delwin(controlwin);
	delwin(guiwin);
}

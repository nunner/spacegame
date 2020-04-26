#include "spacegame.h"

#include <string.h>

#define CONTROL_WIDTH 40

extern WINDOW *mainwindow;
extern ship_t *player;

//static int max_x, max_y;
static WINDOW *guiwin;
static WINDOW *controlwin;

static WINDOW *shieldwin;
static WINDOW *phaserwin;
static WINDOW *boosterwin;

void
print_control_bar(WINDOW *w, int value)
{
	for(int i = 0; i < player->maxenergy; i++)
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
print_controls()
{
	mvwprintw(controlwin, 0, (CONTROL_WIDTH-strlen("Controls"))/2, "Controls");
	mvwprintw(controlwin, 1, 1, "Energy available: %02d/%02d", player->maxenergy-player->energy, player->maxenergy);

	// Controls for shield
	mvwprintw(controlwin, 3, (CONTROL_WIDTH-strlen("Shield"))/2, "Shield");
	mvwprintw(controlwin, 4, 2, "1");
	mvwprintw(controlwin, 4, CONTROL_WIDTH-3, "2");

	print_control_bar(shieldwin, player->controls->shield);

	// Controls for phaser
	mvwprintw(controlwin, 8, (CONTROL_WIDTH-strlen("Phasers"))/2, "Phasers");
	mvwprintw(controlwin, 9, 2, "3");
	mvwprintw(controlwin, 9, CONTROL_WIDTH-3, "4");

	print_control_bar(phaserwin, player->controls->phasers);

	// Controls for boosters
	mvwprintw(controlwin, 13, (CONTROL_WIDTH-strlen("Boosters"))/2, "Boosters");
	mvwprintw(controlwin, 14, 2, "5");
	mvwprintw(controlwin, 14, CONTROL_WIDTH-3, "6");

	print_control_bar(boosterwin, player->controls->booster);
}

void
init()
{
	keypad(guiwin, true);
	box(guiwin, 0, 0);
	box(controlwin, 0, 0);
	box(shieldwin, 0, 0);
	box(phaserwin, 0, 0);
	box(boosterwin, 0, 0);
}

void
show_gui()
{
	guiwin = dupwin(mainwindow);
	controlwin = subwin(guiwin, INIT_LINES, CONTROL_WIDTH, 0, 0);
	shieldwin = subwin(controlwin, 3, CONTROL_WIDTH-8, 3, 4);
	phaserwin = subwin(controlwin, 3, CONTROL_WIDTH-8, 8, 4);
	boosterwin = subwin(controlwin, 3, CONTROL_WIDTH-8, 13, 4);

	init();

	int key = 0;

	while(1)
	{
		print_controls();	
		wrefresh(guiwin);
		wrefresh(controlwin);

		switch((key = wgetch(guiwin))) 
		{
			case 'M':
			case 'm':
				map();
				init();
				break;
			case '1':
				if(player->controls->shield != 0) {
					player->controls->shield--;
					player->energy--;
				}
				break;
			case '2':
				if(player->controls->shield < 15 && player->energy < player->maxenergy) {
					player->controls->shield++;
					player->energy++;
				}
				break;
			case '3':
				if(player->controls->phasers != 0) {
					player->controls->phasers--;
					player->energy--;
				}
				break;
			case '4':
				if(player->controls->phasers < 15 && player->energy < player->maxenergy) {
					player->controls->phasers++;
					player->energy++;
				}
				break;
			case '5':
				if(player->controls->booster != 0) {
					player->controls->booster--;
					player->energy--;
				}
				break;
			case '6':
				if(player->controls->booster < 15 && player->energy < player->maxenergy) {
					player->controls->booster++;
					player->energy++;
				}
				break;

		}
	}

	delwin(guiwin);
}

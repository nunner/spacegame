#include "spacegame.h"

WINDOW *mainwindow;

int
main(void)
{
	initscr();
	noecho();
	curs_set(FALSE);

	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);

	mainwindow = newwin(30, 140, 0, 0);

	map();

	endwin();
}

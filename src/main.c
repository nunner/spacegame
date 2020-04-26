#include "spacegame.h"
#include "ship.h"

WINDOW *mainwindow;

int
main(void)
{
	initscr();
	noecho();
	curs_set(FALSE);

	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);

	mainwindow = newwin(INIT_LINES, INIT_COLS, 0, 0);

	map();
	show_gui();

	endwin();
}

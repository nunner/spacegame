#include "spacegame.h"
#include "ship.h"

WINDOW *mainwindow;

char *main_manu[] = {
	"Start game!",
	"Exit"
};

int
main(void)
{
	initscr();
	noecho();
	curs_set(FALSE);

	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_RED);
	init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(6, COLOR_GREEN, COLOR_GREEN);
	init_pair(7, COLOR_BLACK, COLOR_BLACK);

	mainwindow = newwin(INIT_LINES, INIT_COLS, 0, 0);

	start_game();

	endwin();
}

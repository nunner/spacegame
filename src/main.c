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
	init_pair(C_BAR_RED, COLOR_RED, COLOR_RED);
	init_pair(C_BAR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(C_BAR_GREEN, COLOR_GREEN, COLOR_GREEN);
	init_pair(C_BAR_TRANS, COLOR_BLACK, COLOR_BLACK);

	init_pair(C_RED, COLOR_RED, COLOR_BLACK);
	init_pair(C_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(C_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(C_CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(C_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(C_DEFAULT, COLOR_WHITE, COLOR_BLACK);

	init_pair(C_SELECTED, COLOR_BLACK, COLOR_WHITE);
	init_pair(C_DISABLED, COLOR_RED, COLOR_BLACK);

	mainwindow = newwin(INIT_LINES, INIT_COLS, 0, 0);

	start_game();

	endwin();
}

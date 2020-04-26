#include "state.h"

#include <string.h>

static statewindow *statewin;
static WINDOW *window;

statewindow *
state_peaceful(WINDOW *w)
{
	window = w;

	mvwprintw(window, 0, (CONTROL_WIDTH-strlen("Information"))/2, "Information");

	print_health(window);

	wrefresh(window);
	return statewin;
}

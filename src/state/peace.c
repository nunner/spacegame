#include "state.h"
#include "spacegame.h"

#include <string.h>

extern gamestate_t *state;

static statewindow *statewin;
static WINDOW *window;

statewindow *
state_peaceful(WINDOW *w)
{
	window = w;

	mvwprintw(window, 0, (CONTROL_WIDTH-strlen("Information"))/2, "Information");

	print_health(window);
	mvwprintw(w, 3, 2, "Crew: \t\t%d", state->player->crew);

	wrefresh(window);
	return statewin;
}

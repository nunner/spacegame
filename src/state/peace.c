#include "state.h"
#include "spacegame.h"

#include <string.h>

void 
handle_peaceful(int key)
{

}


void
state_peaceful(WINDOW *w)
{
	mvwprintw(w, 0, (CONTROL_WIDTH-strlen("Information"))/2, "Information");

	print_health(w);
	mvwprintw(w, 3, 2, "Crew: \t\t%d", state->player->crew);

	wrefresh(w);
}

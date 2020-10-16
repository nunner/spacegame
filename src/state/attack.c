#include "spacegame.h"
#include "state.h"

#include <string.h>

int target;

void 
handle_attack(int key)
{

}


void
state_attack(WINDOW *w)
{
	wcolor_set(w, C_RED, 0);
	mvwprintw(w, 0, (CONTROL_WIDTH-strlen("Attack"))/2, "Attack");
	wcolor_set(w, C_DEFAULT, 0);

	wrefresh(w);
}

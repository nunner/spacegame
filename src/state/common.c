#include "spacegame.h"
#include "state.h"

extern gamestate_t *state;

inline void
print_health(WINDOW *w)
{
	mvwprintw(w, 2, 2, "Health: \t\t%d", state->player->health);
}

void
print_status(WINDOW *w, int y, int x, char *name, bool status)
{
	char *s = status ? "OK" : "ALERT";
	if(status)
		wcolor_set(w, C_GREEN, 0);
	else
		wcolor_set(w, C_RED, 0);

	mvwprintw(w, y, x, "%s: \t%s", name, s);

	wcolor_set(w, C_DEFAULT, 0);
}

void
print_energy(WINDOW *w, int y, int x, int value)
{
	wcolor_set(w, C_RED, 0);

	if(value >= 10)
		wcolor_set(w, C_GREEN, 0);
	else if(value >= 5)
		wcolor_set(w, C_YELLOW, 0);

	mvwprintw(w, y, x, "Energy: \t%d", value);

	wcolor_set(w, C_DEFAULT, 0);
}

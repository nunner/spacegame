#include "spacegame.h"
#include "state.h"

extern gamestate_t *state;

void
print_health(WINDOW *w)
{
	mvwprintw(w, 2, 2, "Health: %d", state->player->health);
}

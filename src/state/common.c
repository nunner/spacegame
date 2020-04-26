#include "spacegame.h"
#include "state.h"

extern gamestate_t *state;

inline void
print_health(WINDOW *w)
{
	mvwprintw(w, 2, 2, "Health: \t\t%d", state->player->health);
}

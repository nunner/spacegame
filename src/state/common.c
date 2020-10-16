#include "spacegame.h"
#include "state.h"

extern void state_attack(WINDOW *w);
extern void state_peaceful(WINDOW *w);
extern void state_trade(WINDOW *w);

extern void handle_attack(int key);
extern void handle_peaceful(int key);
extern void handle_trade(int key);

void
check_state() 
{
	switch(state->current_state.val) {
		case ATTACK:
			state->current_state.draw = state_attack;
			state->current_state.handle = handle_attack;
			break;
		case PEACE:
			state->current_state.draw = state_peaceful;
			state->current_state.handle = handle_peaceful;
			break;
		case TRADE:
			state->current_state.draw = state_trade;
			state->current_state.handle = handle_trade;
			break;
	}
}

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

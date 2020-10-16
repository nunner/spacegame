#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <curses.h>

/*
 * Types for the ship
 */ 

typedef struct {
	uint32_t crew;
	uint8_t health;
	uint8_t energy;
	uint8_t maxenergy;
	struct {
		uint16_t shield;
		uint16_t phasers;
		uint16_t booster;
	} controls;
	struct {
		bool machine_deck;
		bool phaser_deck;
		bool engine_deck;
	} status;
} ship_t;

/*
 * Types for the map
 */ 

typedef struct {
	int x, y;
	int index;
	bool visited;
} location_t;

typedef struct {
	location_t locations[LOCATION_COUNT];
} sector_t;

/*
 * Types for storing the current state of the game
 */ 

typedef enum {
	PEACE,
	TRADE,
	ATTACK
} STATE;

typedef struct {
	location_t *current_location;
	sector_t *current_sector;
	ship_t *player;
	struct {
		STATE val;
		void (*draw)(WINDOW *win);
		void (*handle)(int key);
	} current_state;
} gamestate_t;

/*
 * Other types
 */

typedef enum {
	M_SYSTEM,
	M_STATUS,
	M_TRADER,
	M_ATTACKER,
	M_UNKNOWN	
} MESSAGE;

#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint16_t shield;
	uint16_t phasers;
	uint16_t booster;
} controls_t;

typedef struct {
	bool machine_deck;
	bool phaser_deck;
	bool engine_deck;
	bool oxygen;
} status_t;

typedef struct {
	uint32_t crew;
	uint8_t health;
	uint8_t energy;
	uint8_t maxenergy;
	controls_t *controls;
	status_t *status;
} ship_t;

typedef struct {
	int x, y;
	bool visited;
} location_t;

typedef struct {
	location_t locations[LOCATION_COUNT];
} sector_t;

typedef enum {
	PEACE,
	TRADE,
	ATTACK
} STATE;

typedef struct {
	location_t *current_location;
	sector_t *current_sector;
	ship_t *player;
	STATE current_state;
} gamestate_t;

typedef enum {
	SYSTEM,
	STATUS,
	TRADER,
	ATTACKER,
	UNKNOWN	
} MESSAGE;

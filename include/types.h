#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint16_t shield;
	uint16_t phasers;
	uint16_t booster;
} controls_t;

typedef struct {
	uint32_t crew;
	uint8_t health;
	uint8_t energy;
	uint8_t maxenergy;
	controls_t *controls;
} ship_t;

typedef struct {
	int x, y;
	bool visited;
} location_t;

typedef struct {
	location_t locations[LOCATION_COUNT];
} sector_t;

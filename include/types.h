#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint32_t crew;
} ship;

typedef struct {
	int x, y;
	bool visited;
} location_t;

typedef struct {
	location_t locations[LOCATION_COUNT];
} sector_t;

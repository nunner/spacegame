#pragma once

typedef struct {
	int x, y;	
} location_t;

typedef struct {
	location_t locations[LOCATION_COUNT];
} sector_t;

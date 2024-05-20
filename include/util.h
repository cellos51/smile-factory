#ifndef UTIL_H
#define UTIL_H

#include "tonc.h"

static const int movement_lut[3][3] = 
{
	{6, 7, 8},
	{5, 0, 1},
	{4, 3, 2}
};

typedef struct 
{
    int x;
    int y;
} Vector2i;

typedef struct 
{
    FIXED x;
    FIXED y;
} Vector2fx;

#endif // UTIL_H
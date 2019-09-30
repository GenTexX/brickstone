#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

float toRad(float degrees) {
	return (float)(degrees * (M_PI / 180.0f));
}

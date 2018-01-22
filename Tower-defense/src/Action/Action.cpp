#include "Action.h"

Action::Action(uint8_t x, uint8_t y, ACTION_TYPE type, uint32_t cost):
	x(x),
	y(y),
	type(type),
	cost(cost) {}
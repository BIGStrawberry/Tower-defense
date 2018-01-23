#include "Action.h"

Action::Action(uint8_t x, uint8_t y, ACTION_TYPE type, uint32_t actionCost):
	x(x),
	y(y),
	type(type),
	actionCost(actionCost) {}
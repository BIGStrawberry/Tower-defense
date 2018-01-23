#include "Action.h"

Action::Action(uint8_t x, uint8_t y, uint32_t cost, ACTION_TYPE type, TowerType tower_type):
	x(x),
	y(y),
	cost(cost),
	type(type),
	tower_type(tower_type) {}
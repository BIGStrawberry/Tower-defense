#include "ProjectileSlow.h"



ProjectileSlow::ProjectileSlow(sf::RenderWindow & window, float damage, sf::Vector2f position, std::shared_ptr<Enemy> & target, sf::Time& slow_time, float& slow_factor):
	Projectile(window, damage, position, target),
	slow_time(slow_time),
	slow_factor(slow_factor)
{}

void ProjectileSlow::onImpact() {
	target->reduce_speed(slow_factor, slow_time);
	target->decreaseHp(static_cast<int>(damage));
	is_dead = true;
}

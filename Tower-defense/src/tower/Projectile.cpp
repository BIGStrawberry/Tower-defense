#include "Projectile.h"



Projectile::Projectile(sf::RenderWindow & window, float damage, sf::Vector2f position, std::shared_ptr<Enemy> & target):
	speed(10.0f),
	damage(damage),
	is_dead(false),
	body(3),
	window(&window),
	target(target)
{
	body.setFillColor(sf::Color::Black);
	body.setOrigin(sf::Vector2f(3, 3));
	body.setPosition(position);
}


void Projectile::render() const {
	window->draw(body);

}

void Projectile::onImpact() {
	target->decreaseHp(static_cast<int>(damage));
	is_dead = true;
}

void Projectile::update() {
	if (target->state == Enemy::States::Walking) {
		if (body.getGlobalBounds().intersects(target->getBounds())) {
			onImpact();
		}

		sf::Vector2f mypos = body.getPosition();
		sf::Vector2f diff = mypos - target->getPosition();

		float distance_to_unit = std::sqrt(std::pow(diff.x, 2.0f) + std::pow(diff.y, 2.0f));
		body.setPosition(body.getPosition() - sf::Vector2f((diff.x / distance_to_unit)* speed, (diff.y / distance_to_unit)* speed));
	}
	else {
		is_dead = true;
	}
	

}

bool Projectile::isDead() {
	return is_dead;
}

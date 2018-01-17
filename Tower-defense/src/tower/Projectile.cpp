#include "Projectile.h"



Projectile::Projectile(sf::RenderWindow & window, int damage, sf::Vector2f position, std::shared_ptr<Enemy> & target):
	speed(10.0f),
	damage(damage),
	is_alive(true),
	body(3),
	window(window),
	target(target)
{
	body.setFillColor(sf::Color::Black);
	body.setOrigin(sf::Vector2f(3, 3));
	body.setPosition(position);
}


void Projectile::render() {
	window.draw(body);

}

void Projectile::update() {
	if (!target->isDead()) {
		if (body.getGlobalBounds().intersects(target->getBounds())) {
			target->decreaseHp(damage);
			is_alive = false;
		}

		sf::Vector2f mypos = body.getPosition();
		sf::Vector2f diff = mypos - target->getPosition();

		float c = std::sqrt(std::pow(diff.x, 2.0f) + std::pow(diff.y, 2.0f));
		body.setPosition(body.getPosition() - sf::Vector2f((diff.x / c)* speed, (diff.y / c)* speed));
	}
	else {
		is_alive = false;
	}

}

bool Projectile::isAlive() {
	return is_alive;
}

Projectile::~Projectile() {}

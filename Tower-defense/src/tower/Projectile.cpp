#include "Projectile.h"



Projectile::Projectile(sf::RenderWindow & window, float damage, sf::Vector2f position):
	speed(0.1f),
	damage(100),
	is_alive(true),
	body(3),
	window(window)
{
	body.setFillColor(sf::Color::Black);
	body.setOrigin(sf::Vector2f(3, 3));
	body.setPosition(position);
}


void Projectile::render() {
	window.draw(body);

}

void Projectile::update() {
	//if (body.getBoundaries().intersects(target.getBoundaries()){
	//	target.decreaseHp(damage);
	//	is_alive = false;
	//	return;
	// }

	sf::Vector2f enemypos = sf::Vector2f((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y); // temporarily mouse pos

	sf::Vector2f mypos = body.getPosition();
	sf::Vector2f diff = mypos - enemypos;

	float c = std::sqrt(std::pow(diff.x, 2.0f) + std::pow(diff.y, 2.0f));
	body.setPosition(mypos - sf::Vector2f((diff.x / c)* speed, (diff.y / c)* speed));

}

bool Projectile::isAlive() {
	return is_alive;
}

Projectile::~Projectile() {}

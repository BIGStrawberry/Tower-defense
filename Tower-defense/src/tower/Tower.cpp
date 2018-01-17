#include "Tower.h"



Tower::Tower(sf::RenderWindow & window, float size, sf::Vector2f pos):
	range_radius(20),
	turret_length(range_radius/2),
	cool_down(1000),
	cool_down_counter(0),
	render_range(true),
	window(window),
	range_circle(static_cast<float>(range_radius)),
	tower_shape(sf::Vector2f(size, size)),
	turret(sf::VertexArray(sf::LinesStrip, 2))

{

	turret[0].position = pos;
	turret[0].color = sf::Color::Black;
	turret[1].color = sf::Color::Black;
	tower_shape.setOrigin(sf::Vector2f(size/2, size/2));
	range_circle.setOrigin(sf::Vector2f(static_cast<float>(range_radius), static_cast<float>(range_radius)));
	range_circle.setFillColor(sf::Color::Transparent);
	range_circle.setOutlineColor(sf::Color::Black);
	range_circle.setOutlineThickness(1.0);

	tower_shape.setPosition(pos);
	range_circle.setPosition(pos);

}


Tower::~Tower()
{
}


void Tower::render() {
	window.draw(tower_shape);
	window.draw(turret);
	if (render_range) {
		window.draw(range_circle);
	}
	sf::Vector2f enemypos(1200, 700);
	sf::CircleShape temp(10.0);
	temp.setPosition(enemypos);
	window.draw(temp);

	for (auto& pt : projectiles) {
		pt->render();
	}
}

void Tower::update() {
	sf::Vector2f mypos = tower_shape.getPosition();
	if (++cool_down_counter >= cool_down /* && target != nullptr */) {
		projectiles.push_back(std::make_unique<Projectile>(window, 10.0f, mypos));
		cool_down_counter = 0;
	}

	sf::Vector2f enemypos = sf::Vector2f((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y);
	sf::Vector2f diff = mypos - enemypos;
	float distance_to_target = std::sqrt(std::pow(diff.x, 2.0f) + std::pow(diff.y, 2.0f));
	//if (distance_to_target > range_radius){
	//for enemy in vector:
	//	diff = mypos - enemypos;
	//	distance_to_enemy = std::sqrt(std::pow(diff.x, 2.0f) + std::pow(diff.y, 2.0f));
	//	if (distance_to_enemy > range_radius){
	//		target = enemy;
	//		
	//		break;
	//	

	float scale = distance_to_target / turret_length;
	turret[1].position = mypos - sf::Vector2f(diff.x / scale, diff.y / scale);


	for (unsigned int i = 0; i < projectiles.size(); ++i) {
		if (projectiles[i]->isAlive()) {
			projectiles[i]->update();
		}
		else {
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
	}


}

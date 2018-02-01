#include "EnemyAir.h"



EnemyAir::EnemyAir(sf::RenderWindow& window, const std::vector<sf::Vector2f>& path, EnemyType type, uint16_t waveNumber):
	Enemy(window, path, type, waveNumber) {
	next_target_pos = *(path.end() - 1);
	distance = sqrt(pow(data.body.getPosition().x - next_target_pos.x, 2) + pow(data.body.getPosition().y - next_target_pos.y, 2));
	vector = (next_target_pos - data.body.getPosition()) / distance;
}


EnemyAir::~EnemyAir() {}

void EnemyAir::update() {
	//Air unit has reached base
	if (data.speed > distance) {
		data.body.setPosition(next_target_pos);
		state = States::Reached_Base;
	} else {
		data.body.setPosition(data.body.getPosition() + (vector * data.speed));
		distance -= data.speed;

	}

	if (slowed) {
		if (slow_timer.getElapsedTime() >= slow_duration) {
			slowed = false;
			data.speed = original_speed;
		}
	}
	bar.setPosition(data.body.getPosition());

}
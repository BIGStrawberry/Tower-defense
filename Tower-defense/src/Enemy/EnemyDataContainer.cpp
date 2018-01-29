#include "EnemyDataContainer.h"

std::map<EnemyType, EnemyData> EnemyDataContainer::container;

void EnemyDataContainer::load()
{

	sf::Sprite body;
	body.setTexture(TextureContainer::get("sonic.png"));
	body.setOrigin(16.f, 16.f);
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Fast, EnemyData{6, 6, 1, 25, body})); // hp , speed, damage, gold

	body.setTexture(TextureContainer::get("knuckle.png"));
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Normal, EnemyData{6, 3, 1, 15, body}));

	body.setTexture(TextureContainer::get("tank.png"));
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Tank, EnemyData{10, 2, 1, 25, body}));

	body.setTexture(TextureContainer::get("tails.png"));
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Flying, EnemyData{6, 3, 1, 20, body}));

}

EnemyData& EnemyDataContainer::get(EnemyType type)
{
	return container[type];
}
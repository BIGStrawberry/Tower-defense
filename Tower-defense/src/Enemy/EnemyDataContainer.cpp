#include "EnemyDataContainer.h"

std::map<EnemyType, EnemyData> EnemyDataContainer::container;

void EnemyDataContainer::load()
{

	sf::Sprite body;
	body.setTexture(TextureContainer::get("sonic.png"));
	body.setOrigin(16.f, 16.f);
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Fast, EnemyData{10, 8, 0, 15, body})); // hp , speed, damage, gold
	body.setTexture(TextureContainer::get("knuckle.png"));
	body.setOrigin(16.f, 16.f);
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Normal, EnemyData{6, 3, 0, 15, body}));

	body.setTexture(TextureContainer::get("tank.png"));

	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Tank, EnemyData{8, 2, 0, 15, body}));
	body.setTexture(TextureContainer::get("tails.png"));
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Flying, EnemyData{15, 4, 0, 15, body}));

}

EnemyData& EnemyDataContainer::get(EnemyType type)
{
	return container[type];
}
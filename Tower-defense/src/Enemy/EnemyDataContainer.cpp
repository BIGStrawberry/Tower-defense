#include "EnemyDataContainer.h"

std::map<EnemyType, EnemyData> EnemyDataContainer::container;

void EnemyDataContainer::load()
{

	sf::Sprite body;
	body.setTexture(TextureContainer::get("sonic.png"));
	body.setOrigin(16.f, 16.f);
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Fast, EnemyData{4, 6, 1, 15, body})); // hp , speed, damage, gold

	body.setTexture(TextureContainer::get("knuckle.png"));
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Normal, EnemyData{6, 3, 1, 15, body}));

	body.setTexture(TextureContainer::get("tank.png"));
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Tank, EnemyData{8, 2, 1, 15, body}));

	body.setTexture(TextureContainer::get("tails.png"));
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Flying, EnemyData{6, 3, 1, 15, body}));

	body.setScale(sf::Vector2f(1.5f, 1.5f));
	body.setTexture(TextureContainer::get("tails.png"));
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Boss_Flying, EnemyData{50, 0.33f, 3, 100, body}));

	body.setScale(sf::Vector2f(1.5f, 1.5f));
	body.setTexture(TextureContainer::get("tank.png"));
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Boss_Tank, EnemyData{50, 1, 3, 100, body}));

	body.setScale(sf::Vector2f(1.5f, 1.5f));
	body.setTexture(TextureContainer::get("sonic.png"));
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Boss_Fast, EnemyData{50, 1, 3, 100, body}));

	body.setScale(sf::Vector2f(3.5f, 3.5f));
	body.setTexture(TextureContainer::get("knuckle.png"));
	container.insert(std::pair<EnemyType, EnemyData>(EnemyType::Ubeah_Knucklez, EnemyData{500, 0.05f, 5, 1000, body}));
}

EnemyData& EnemyDataContainer::get(EnemyType type)
{
	return container[type];
}
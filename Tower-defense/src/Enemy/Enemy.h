#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Grid
{
public:
	std::vector<sf::Vector2f> path;
};

class Enemy
{
protected:
	sf::RenderWindow& window;
	Grid& grid;
	int target_counter;
	float distance;
	sf::CircleShape circle;
	sf::Vector2f next_target_pos;
	sf::Vector2f vector;
	float speed;
	int hp;
	int dmg;
	int gold;
	bool dead;

public:
	Enemy(sf::RenderWindow& window, Grid& grid);
	~Enemy();

	void decreaseHp(int dmg);
	sf::Vector2f getPosition();
	void render();
	virtual void update() = 0;
};

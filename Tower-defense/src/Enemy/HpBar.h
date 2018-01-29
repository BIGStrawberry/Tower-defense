#pragma once
#include "SFML\Graphics.hpp"

class HpBar
{
private:
	float length;
	float thickness;
	float height;
	sf::RectangleShape red;
	sf::RectangleShape green;
	float multiplier;

	bool to_render;
public:
	HpBar(float hp);

	void setHp(float Hp);
	void setPosition(sf::Vector2f pos);
	void render(sf::RenderWindow& window) const;
};
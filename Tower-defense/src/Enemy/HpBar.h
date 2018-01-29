#pragma once
#include "SFML\Graphics.hpp"

/**
* @class HpBar
@brief This class represents the hp bar, shown above every enemy.
*/

class HpBar
{
private:
	float length;
	float thickness;
	float height;
	sf::RectangleShape red;
	sf::RectangleShape green;
	float multiplier;
	sf::Clock clock;

	bool to_render;
public:
	/**
	* @brief Constructor
	* @param float - The starting hp of the unit.
	*/
	HpBar(float hp);

	/**
	* @brief updates hp bar
	* @details This function needs to be called when hp of unit is changed.
	* Hp bar will be updated.
	*/
	void setHp(float Hp);

	/**
	* @brief updates position of hp bar
	* @param pos - sf::Vector2f position of unit.
	* @details This function must be called once per gameloop, 
	* because it handles the cooldown timer. This would better be
	* in render(), but someone made that const, so it needs to be done here.
	*/
	void setPosition(sf::Vector2f pos);

	/**
	* @brief renders the hp bar, if needed. Wont render anything if
	* no damage taken in the last x seconds.
	*/
	void render(sf::RenderWindow& window) const;
};
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "EnemyType.h"
#include "EnemyDataContainer.h"


#pragma region comment
/**
* @class Enemy
* @file Enemy.cpp
* @brief Class for enemy units
* @details This is an abstract base class for enemy units.
* Enemies can be updated and rendered.
*/
#pragma endregion
class Enemy
{
protected:
	sf::RenderWindow& window;
	const std::vector<sf::Vector2f>& path;
	float distance;
	sf::CircleShape body;
	sf::Vector2f next_target_pos;
	sf::Vector2f vector;
	float speed;
	float original_speed;
	int hp;
	int dmg;
	int gold;

	sf::Clock slow_timer;
	bool slowed;
	sf::Time slow_duration;

public:
	#pragma region comment
	/**
	* @brief States for Enemies that indicate if the enemy is either moving/dead/reached the base
	*/

	#pragma endregion
	enum class States {
		Walking, Dead, Reached_Base
	};
	States state = States::Walking;

public:
#pragma region comment
	/**
	* @brief Enemy Constructor
	* @param sf::RenderWindow&			window: SFML window instance to be rendered on.
	* @param std::vector<sf::Vector2f>&	path: Vector reference, which contains (at least 1) coordinate point(s).
	*									The enemy will follow the given path, until it reaches the base (last coordinate).
	* @param EnemyType					Type of the Enemy.
	*/

#pragma endregion
	Enemy(sf::RenderWindow& window, const std::vector<sf::Vector2f>& path, EnemyType type);
	~Enemy();

#pragma region comment
	/**
	* @brief decreases hp of Enemy
	* @param int	dmg: Amount of damage that is being dealt.
	* @details This function needs to be called by a projectile instance,
	* when it deals damage to the Enemy. If there is no more hitpoints
	* remaining after the hit, bool dead will be set to true. After this
	* is done, the Enemy won't react to future update() calls, nor can be
	* rendered. Object is ready to be removed from the container.
	*/

#pragma endregion
	void decreaseHp(int dmg);
#pragma region comment
	/**
	* @brief returns Enemy's position
	* @details This function returns the sf::Vector2f position
	* of the Enemy.
	*/

#pragma endregion
	const sf::Vector2f getPosition() const;
#pragma region comment
	/**
	* @brief renders Enemy
	* @details This function renders the Enemy to the sf::RenderWindow reference
	* stored in a member variable. Will only render if unit is not marked as dead.
	*/

#pragma endregion
	void render() const;
#pragma region comment
	/**
	* @brief abstract update funcion
	* @details This function is to be called once per update loop.
	*/

#pragma endregion
	virtual void update() = 0;
#pragma region comment
	/**
	* @brief returns dmg attribute
	* @details This function returns the amount of damage the player would take when this enemy reaches the base.
	*/

#pragma endregion
	const int getDmg() const;
#pragma region comment
	/**
	* @brief returns gold attribute
	* @details This function returns the amount of gold that the player
	* gets in case Enemy gets killed.
	*/

#pragma endregion
	const int getGold() const;
#pragma region comment
	/**
	* @brief returns bounding box
	* @details This function returns an sf::FloatRect object, that can be used
	* to check overlap with the Enemy instance.
	*/

#pragma endregion
	sf::FloatRect getBounds() const;

	#pragma region comment
	/**
	* @brief slows target by half for given time.
	* @details This function reduces the speed by multiplying it with factor, it resets the slow_timer and sets the boolean slowed on true.
	*
	*/

	void reduce_speed(float factor, sf::Time time);
	#pragma endregion

};
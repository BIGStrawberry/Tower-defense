#pragma once

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>

class SpearMan {
private:
	static constexpr const float energyBarWidth = 32;
	static constexpr const float energyBarHeight = 5;
	enum class STATE {
		normal,
		thrusting,
		defending,
		clashing,
		stunned,
		dead
	};

	sf::RenderWindow* window;
	sf::Sound thrustSound, defendSound, clashSound, hurtSound;
	sf::Sprite body, spear, spearTip;
	sf::RectangleShape spearTipHitbox;
	sf::CircleShape bodyHitbox;
	sf::CircleShape energyOne, energyTwo, energyThree;
	sf::Vector2f position, velocity;
	sf::Clock energyClock, stunnedClock;
	const sf::Time energyRegenDelay = sf::seconds(2.5f), stunnedTime = sf::seconds(0.35f);
	const float maxAcceleration = 5, accelerationSpeed = 0.3f;
	float rotation, speed = 5, acceleration = 1;
	STATE state = STATE::normal;
	const int8_t maxEnergy = 3, thrustCost = 1, defendCost = 2;
	int8_t energy;
public:
	const uint8_t id;
	bool leftTriggerPressed = false, rightTriggerPressed = false;
public:
	/**
	* @brief constructor
	* @param window SFML window to draw on
	* @param body SFML Sprite for the body of the SpearMan
	* @param spear SFML Sprite for the spear of the SpearMan
	* @param position Starting position of the SpearMan
	* @param rotation Starting rotation of the SpearMan
	*/
	SpearMan(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites, const std::vector<sf::Sound>& sounds, const sf::Color color, uint8_t id, sf::Vector2f position, float rotation = 0);

	/**
	* @brief Returns if spearMan is in dead state
	*/
	bool isDead() const { return state == STATE::dead; }

	/**
	* @brief calculates the angle between own position and given vector, the sets it to the rotation of SpearMan
	* @param otherPosition The other vector
	*/
	void setRotation(sf::Vector2f otherPosition);
	/**
	* @brief Uses the setRotation function to set the rotation
	* @param joystickPosition Vector with 2 joystick axis positions.
	*
	* @details
	* Calls the setRotations function with the SpearMan current position + the Joystick axis positions
	*/
	void setRotationJoystick(sf::Vector2f joystickPosition);

	/**
	* @brief Makes the SpearMan thrust
	*
	* @details
	* Checks if there is enough energy, then if there is it will removes the thrust cost from energy and sets isThrusting to true for the update function
	*/
	void thrust();
	/**
	* @brief Makes the SpearMan defend
	*
	* @details
	* Checks if there is enough energy, then if there is it will removes the defend cost from energy and sets isDefending to true for the update function
	*/
	void defend();

	/**
	* @brief handle Collision
	*/
	void handleCollision(const SpearMan& other);

	/**
	* @brief Updates the SpearMan
	*/
	void update();
	/**
	* @brief Updates the SpearMan
	*/
	void render() const;
};


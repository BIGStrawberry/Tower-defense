#include "SpearMan.h"

SpearMan::SpearMan(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites, const std::vector<sf::Sound>& sounds, const sf::Color color, uint8_t id, sf::Vector2f position, float rotation):
	window(&window),
	thrustSound(sounds[0]),
	defendSound(sounds[1]),
	clashSound(sounds[2]),
	hurtSound(sounds[3]),
	body(sprites[0]),
	spear(sprites[1]),
	spearTip(sprites[2]),
	spearTipHitbox(sf::Vector2f{static_cast<float>(spearTip.getTexture()->getSize().x), static_cast<float>(spearTip.getTexture()->getSize().y)}),
	bodyHitbox(9),
	energyOne(4),
	energyTwo(4),
	energyThree(4),
	position(position),
	rotation(rotation),
	energy(maxEnergy),
	id(id) {
	bodyHitbox.setOrigin(bodyHitbox.getGlobalBounds().width / 2, bodyHitbox.getGlobalBounds().height / 2);
	spearTipHitbox.setOrigin(spearTip.getOrigin());
	body.setColor(color);
}

void SpearMan::setRotation(sf::Vector2f otherPosition) {
	// Prevent rotation when thrusting or defending
	if (state == STATE::normal) {
		rotation = atan2(otherPosition.y - position.y, otherPosition.x - position.x);
	}
}

void SpearMan::setRotationJoystick(sf::Vector2f joystickPosition) {
	setRotation(position + joystickPosition);
}

void SpearMan::thrust() {
	// Trying to thrust while still thrusting/defending cost energy (to prevent spamming)
	if (energy >= thrustCost) {
		energy -= thrustCost;
		if (state == STATE::normal) {
			state = STATE::thrusting;
			thrustSound.play();
		}
	}
}

void SpearMan::defend() {
	// Trying to defend while still thrusting/defending cost energy (to prevent spamming)
	if (energy >= defendCost) {
		energy -= defendCost;
		if (state == STATE::normal) {
			state = STATE::defending;
			defendSound.play();
		}
	}
}

void SpearMan::handleCollision(const SpearMan& other) {
	// Oef!
	if (bodyHitbox.getGlobalBounds().intersects(other.spearTipHitbox.getGlobalBounds())) {
		body.setColor({33,33,33});
		state = STATE::dead;
		hurtSound.play();
	}
	// if State not equals defending and spearTip hits other spearTip or if other is defending and spearTip hits other spear
	else if ((state != STATE::defending && spearTipHitbox.getGlobalBounds().intersects(other.spearTipHitbox.getGlobalBounds())) ||
		(other.state == STATE::defending && spearTipHitbox.getGlobalBounds().intersects(other.spear.getGlobalBounds()))
			 ) {
		state = STATE::clashing;
		clashSound.play();
	}
}

void SpearMan::update() {
	switch (state) {
	case SpearMan::STATE::normal:
		// Calculate velocity based on rotation
		velocity.x = speed * static_cast<float>(cos(rotation));
		velocity.y = speed * static_cast<float>(sin(rotation));

		// Regenerate energy
		if (energyClock.getElapsedTime() > energyRegenDelay) {
			if (energy < maxEnergy) {
				energy += 1;
			}
			energyClock.restart();
		}
		stunnedClock.restart();
		break;
	case SpearMan::STATE::thrusting:
		acceleration += accelerationSpeed;
		position.x += velocity.x * acceleration;
		position.y += velocity.y * acceleration;

		if (acceleration > maxAcceleration) {
			acceleration = 1;
			state = STATE::normal;
		}
		break;
	case SpearMan::STATE::defending:
		acceleration += accelerationSpeed;
		velocity.x = 0;
		velocity.y = 0;
		rotation += acceleration;

		if (acceleration > maxAcceleration) {
			acceleration = 1;
			state = STATE::normal;
		}
		break;
	case SpearMan::STATE::clashing:
		// TODO: Better clashing
		// Calculate velocity based on rotation
		velocity.x = -speed * static_cast<float>(cos(rotation));
		velocity.y = -speed * static_cast<float>(sin(rotation));

		acceleration += accelerationSpeed;
		position.x += velocity.x * acceleration;
		position.y += velocity.y * acceleration;

		if (acceleration > maxAcceleration / 2) {
			acceleration = 1;
			state = STATE::stunned;
		}
		break;
	case SpearMan::STATE::stunned:
		velocity.x = 0;
		velocity.y = 0;

		if (stunnedClock.getElapsedTime() > stunnedTime) {
			state = STATE::normal;
		}
		break;
	}

	// Move
	position += velocity;

	// Prevent SpearMan from going out of bounds
	sf::Vector2f windowSize = {
		static_cast<float>(window->getSize().x),
		static_cast<float>(window->getSize().y)
	};
	if (position.x < 0) {
		position.x = 0;
	} else if (position.x > windowSize.x) {
		position.x = windowSize.x;
	}

	if (position.y < 0) {
		position.y = 0;
	} else if (position.y > windowSize.y) {
		position.y = windowSize.y;
	}

	body.setPosition(position);
	spear.setPosition(position);
	spearTip.setPosition(position);

	float rotationInDegrees = rotation / 3.141592654f * 180;
	body.setRotation(rotationInDegrees);
	spear.setRotation(rotationInDegrees);
	spearTip.setRotation(rotationInDegrees);

	// Collision boxes
	bodyHitbox.setPosition(position);
	bodyHitbox.setRotation(rotationInDegrees);
	spearTipHitbox.setPosition(position);
	spearTipHitbox.setRotation(rotationInDegrees);

	// TODO: Replace this with texures
	sf::Vector2f energyPosition = position - sf::Vector2f{body.getOrigin().x, 24};
	energyOne.setPosition(energyPosition);
	energyTwo.setPosition(energyPosition + sf::Vector2f{12, 0});
	energyThree.setPosition(energyPosition + sf::Vector2f{24, 0});
}

void SpearMan::render() const {
	// window->draw(spearTipHitbox);
	window->draw(spearTip);
	window->draw(spear);
	window->draw(body);
	if (energy > 0) window->draw(energyOne);
	if (energy > 1) window->draw(energyTwo);
	if (energy > 2) window->draw(energyThree);
	// window->draw(bodyHitbox);
}



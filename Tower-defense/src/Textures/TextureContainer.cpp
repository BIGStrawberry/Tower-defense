#include "TextureContainer.h"
#include <iostream>


std::map<std::string, std::shared_ptr<sf::Texture>> TextureContainer::container;

sf::Texture& TextureContainer::get(std::string name) {
	return *container[name];
}


void TextureContainer::load() {
	auto temp = std::make_shared<sf::Texture> ();
	temp->loadFromFile("resources/textures/normal_turret.png");
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("normal_turret.png", temp));

	temp = std::make_shared<sf::Texture>();
	temp->loadFromFile("resources/textures/slow_turret.png");
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("slow_turret.png", temp));

	temp = std::make_shared<sf::Texture>();
	temp->loadFromFile("resources/textures/long_turret.png");
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("long_turret.png", temp));

	temp = std::make_shared<sf::Texture>();
	temp->loadFromFile("resources/textures/base.png");
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("base.png", temp));

	temp = std::make_shared<sf::Texture>();
	temp->loadFromFile("resources/textures/knuckle.png");
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("knuckle.png", temp));

	temp = std::make_shared<sf::Texture>();
	temp->loadFromFile("resources/textures/sonic.png");
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("sonic.png", temp));

	temp = std::make_shared<sf::Texture>();
	temp->loadFromFile("resources/textures/tails.png");
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("tails.png", temp));

	temp = std::make_shared<sf::Texture>();
	temp->loadFromFile("resources/textures/tank.png");
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("tank.png", temp));
}
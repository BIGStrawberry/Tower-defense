#include "TextureContainer.h"
#include <iostream>


std::map<std::string, std::shared_ptr<sf::Texture>> TextureContainer::container;

sf::Texture& TextureContainer::get(std::string name) {
	return *container[name];
}


void TextureContainer::load() {
	auto temp = std::make_shared<sf::Texture> ();
	if (!temp->loadFromFile("resources/textures/normal_turret.png")) {
		std::cout << "not loaded";
	}
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("normal_turret.png", temp));
	auto temp1 = std::make_shared<sf::Texture>();
	if (!temp1->loadFromFile("resources/textures/slow_turret.png")) {
		std::cout << "not loaded";
	}
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("slow_turret.png", temp1));
	auto temp2 = std::make_shared<sf::Texture>();
	if (!temp2->loadFromFile("resources/textures/long_turret.png")) {
		std::cout << "not loaded";
	}
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("long_turret.png", temp2));

	auto temp3 = std::make_shared<sf::Texture>();
	if (!temp3->loadFromFile("resources/textures/base.png")) {
		std::cout << "not loaded";
	}
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("base.png", temp3));

	auto temp4 = std::make_shared<sf::Texture>();
	if (!temp4->loadFromFile("resources/textures/knuckle.png")) {
		std::cout << "not loaded";
	}
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("knuckle.png", temp4));


	auto temp5 = std::make_shared<sf::Texture>();
	if (!temp5->loadFromFile("resources/textures/sonic.png")) {
		std::cout << "not loaded";
	}
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("sonic.png", temp5));

	auto temp6 = std::make_shared<sf::Texture>();
	if (!temp6->loadFromFile("resources/textures/tails.png")) {
		std::cout << "not loaded";
	}

	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("tails.png", temp6));
	auto temp7 = std::make_shared<sf::Texture>();
	if (!temp7->loadFromFile("resources/textures/tank.png")) {
		std::cout << "not loaded";
	}
	container.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>("tank.png", temp7));
}
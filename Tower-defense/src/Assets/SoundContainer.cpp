#include "SoundContainer.h"


std::map<std::string, std::shared_ptr<sf::SoundBuffer>> SoundContainer::container;


void SoundContainer::load() {
	auto temp = std::make_shared<sf::SoundBuffer>();
	temp->loadFromFile("resources/sounds/wave_start.wav");
	container.insert(std::pair<std::string, std::shared_ptr<sf::SoundBuffer>>("wave_start.wav", temp));

	temp = std::make_shared<sf::SoundBuffer>();
	temp->loadFromFile("resources/sounds/construction_tower.wav");
	container.insert(std::pair<std::string, std::shared_ptr<sf::SoundBuffer>>("construction_tower.wav", temp));

	temp = std::make_shared<sf::SoundBuffer>();
	temp->loadFromFile("resources/sounds/enemy_dying.wav");
	container.insert(std::pair<std::string, std::shared_ptr<sf::SoundBuffer>>("enemy_dying.wav", temp));

	temp = std::make_shared<sf::SoundBuffer>();
	temp->loadFromFile("resources/sounds/wave_victory.wav");
	container.insert(std::pair<std::string, std::shared_ptr<sf::SoundBuffer>>("wave_victory.wav", temp));

	temp = std::make_shared<sf::SoundBuffer>();
	temp->loadFromFile("resources/sounds/menu_click.wav");
	container.insert(std::pair<std::string, std::shared_ptr<sf::SoundBuffer>>("menu_click.wav", temp));


}

sf::SoundBuffer& SoundContainer::get(std::string name) {
	return *container[name];
}
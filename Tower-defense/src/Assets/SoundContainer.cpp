#include "SoundContainer.h"


std::map<std::string, std::shared_ptr<sf::SoundBuffer>> SoundContainer::container;


void SoundContainer::load() {
	auto temp = std::make_shared<sf::SoundBuffer>();
	temp->loadFromFile("resources/sounds/wave_start.ogg");
	container.insert(std::pair<std::string, std::shared_ptr<sf::SoundBuffer>>("wave_start.ogg", temp));

	temp = std::make_shared<sf::SoundBuffer>();
	temp->loadFromFile("resources/sounds/construction_tower.ogg");
	container.insert(std::pair<std::string, std::shared_ptr<sf::SoundBuffer>>("construction_tower.ogg", temp));

	temp = std::make_shared<sf::SoundBuffer>();
	temp->loadFromFile("resources/sounds/enemy_dying.ogg");
	container.insert(std::pair<std::string, std::shared_ptr<sf::SoundBuffer>>("enemy_dying.ogg", temp));

	temp = std::make_shared<sf::SoundBuffer>();
	temp->loadFromFile("resources/sounds/wave_victory.ogg");
	container.insert(std::pair<std::string, std::shared_ptr<sf::SoundBuffer>>("wave_victory.ogg", temp));

	temp = std::make_shared<sf::SoundBuffer>();
	temp->loadFromFile("resources/sounds/menu_click.ogg");
	container.insert(std::pair<std::string, std::shared_ptr<sf::SoundBuffer>>("menu_click.ogg", temp));

	temp = std::make_shared<sf::SoundBuffer>();
	temp->loadFromFile("resources/sounds/enemy_reached_base.ogg");
	container.insert(std::pair<std::string, std::shared_ptr<sf::SoundBuffer>>("enemy_reached_base.ogg", temp));

}

sf::SoundBuffer& SoundContainer::get(std::string name) {
	return *container[name];
}
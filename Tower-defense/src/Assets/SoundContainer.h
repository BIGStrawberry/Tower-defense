#pragma once
#include <SFML/graphics.hpp>
#include <SFML/audio.hpp>
#include <memory>

#pragma region comment
/**
* @class A container for all the sounds.
* @file SoundContainer.h
* @details This is a static class, that contains all the soundBuffers.
* Sounds can be retrieved here with a string as key.
* Load has to be called at the start of the game, before every container that uses sounds.
*/
#pragma endregion

class SoundContainer {
private:
	static std::map<std::string, std::shared_ptr<sf::SoundBuffer>> container;
public:
	/**
	* @brief returns a SoundBuffer reference of the filename in parameters.
	*/
	static sf::SoundBuffer& get(std::string name);

	/**
	* @brief loads the textures to the container, with as key their filename.
	* @details This function loads all the data to the container.
	* Needs to be called before constructing any object that uses a Sound.
	*/
	static void load();
};


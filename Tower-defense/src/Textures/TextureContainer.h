#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>


#pragma region comment
/**
* @class A container for all the textures
* @file TextureContainer.cpp
* @details This is a static class, that contains all the textures.
* Textures can be retrieved here with a string as key.
* Load has to be called at the start of the game, before all other containers.
*/
#pragma endregion

class TextureContainer {
private:
	static std::map<std::string, std::shared_ptr<sf::Texture>> container;
	// Disallow creating an instance of this object
	TextureContainer() {};

public:
	/**
	* @brief returns a texture reference of the filename in parameters.
	*/
	static sf::Texture& get(std::string name);

	/**
	* @brief loads the textures to the container, with as key their filename.
	* @details This function loads all the data to the container.
	* Needs to be called before constructing any object that uses a texture.
	*/
	static void load();
};


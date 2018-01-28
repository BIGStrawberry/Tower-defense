#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>

class TextureContainer {
private:
	static std::map<std::string, std::shared_ptr<sf::Texture>> container;
public:
	static sf::Texture& get(std::string name);
	static void load();
};


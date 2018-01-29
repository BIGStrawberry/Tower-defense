#include "ToggleFullscreen.h"

/**
* @brief Toggles Fullscreen mode
* @param window SFML renderwindow that needs to be toggled
*
* @details
* Creates a new window with Fullscreen or not fullscreen depending on Settings fullscreen attrubute
*/
void toggleFullscreen(sf::RenderWindow& window) {
	sf::VideoMode resolution(1280, 720);
	std::string title = "A mazing tower defence";
	Settings::FULLSCREEN = !Settings::FULLSCREEN;
	window.create(resolution, title, (Settings::FULLSCREEN) ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
}
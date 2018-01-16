#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Helpers/GameStateManager.h"
#include "States/MenuState.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Game State Manager");
	sf::Event event;

	// The game starts in the MenuState
	GameStateManager::pushState(std::make_shared<MenuState>(window));

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		/**********/
		/**UPDATE**/
		/**********/
		// TODO: game loop
		// Update the active state
		GameStateManager::getCurrentState()->update();
		/**********/
		/**RENDER**/
		/**********/
		window.clear(sf::Color(200, 200, 200));
		// Draw the active state
		GameStateManager::getCurrentState()->render();
		window.display();
	}

	return 0;
}
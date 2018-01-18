#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Helpers/GameStateManager.h"
#include "States/MenuState.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Game State Manager");
	sf::Event evt;

	// The game starts in the MenuState
	GameStateManager::pushState(std::make_shared<MenuState>(window));

	while (window.isOpen()) {
		while (window.pollEvent(evt)) {
			switch (evt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				GameStateManager::getCurrentState()->onKeyPressed(evt);
				break;
			case sf::Event::KeyReleased:
				GameStateManager::getCurrentState()->onKeyReleased(evt);
				break;
			case sf::Event::MouseButtonPressed:
				GameStateManager::getCurrentState()->onMouseButtonPressed(evt);
				break;
			case sf::Event::MouseButtonReleased:
				GameStateManager::getCurrentState()->onMouseButtonReleased(evt);
				break;
			case sf::Event::MouseMoved:
				GameStateManager::getCurrentState()->onMouseMoved(evt);
				break;
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
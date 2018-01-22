#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Helpers/GameStateManager.h"
#include "States/MenuState.h"

/*
Gameloop
The update method of the current state is called 60 times per second.
This is done by keeping up the time that has passed between the last and the current update
and when the time is bigger than 1/60th of a second the currentstate update method is called.
The input and render methods are called the remaining time.
Every second the update and render counter will be set in the title as updates per second and frames per second.

*/

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Game State Manager");
	sf::Event evt;

	// The game starts in the MenuState
	GameStateManager::pushState(std::make_shared<MenuState>(window));

	int update_counter = 0;
	int render_counter = 0;

	const sf::Time time_per_update = sf::seconds(1.f / 60.f);
	const sf::Time second = sf::seconds(1);
	sf::Clock update_clock;
	sf::Clock stats_clock;

	sf::Time delta_time; // time between last update and current update call
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
		sf::Time elapsedTime = update_clock.restart();
		delta_time += elapsedTime;
		while (delta_time >= time_per_update) {
			delta_time -= time_per_update;
			update_counter++;
			// Update the active state
			GameStateManager::getCurrentState()->update();
		}

		/**********/
		/**RENDER**/
		/**********/
		window.clear(sf::Color(200, 200, 200));
		// Draw the active state
		GameStateManager::getCurrentState()->render();
		window.display();
		render_counter++;

		sf::sleep(time_per_update); // call this when you want to limit your fps

		//update fps and ups 
		if (stats_clock.getElapsedTime() > sf::seconds(1)) {
			stats_clock.restart();
			std::string temp = "ups = " + std::to_string(update_counter) + " fps = " + std::to_string(render_counter);
			window.setTitle(temp);
			update_counter = render_counter = 0;
		}

	}

	return 0;
}
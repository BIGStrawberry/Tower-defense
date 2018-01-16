#include "MenuItem.h"

#include <iostream>

MenuItem::MenuItem(sf::RenderWindow& window, std::function<void()> action, sf::Vector2f size, sf::Vector2f position, sf::Text text):
	window(window),
	action(action),
	button(size),
	text(text)
{
	// TODO set text font
	button.setPosition(position);
	this->text.setFillColor(sf::Color{0,0,0});
	// Center text inside the button
	// TODO this does not work for some reason
	sf::FloatRect textRect = text.getLocalBounds();
	this->text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2);
	this->text.setPosition({position.x, position.y});
}

void MenuItem::render() const {
	// TODO draw button with text in middle
	window.draw(button);
	window.draw(text);
}

void MenuItem::onPress() {
	action();
}
#include "MenuItem.h"

#include <iostream>

MenuItem::MenuItem(sf::RenderWindow& window, std::function<void()> action, sf::Vector2f size, sf::Vector2f position, sf::Text text):
	window(window),
	action(action),
	button(size),
	text(text)
{
	button.setPosition(position);
	this->text.setFillColor(sf::Color{0,0,0});
	// Center text inside the button
	// TODO this does not work
	sf::FloatRect textRect = text.getLocalBounds();
	this->text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	// this->text.setPosition({position.x, position.y}); // We should use this one but it does not work
	this->text.setPosition({position.x + size.x / 4, position.y + size.y / 1.5f});
}

void MenuItem::onPress() {
	action();
}

void MenuItem::render() const {
	// TODO draw button with text in middle
	window.draw(button);
	window.draw(text);
}

void MenuItem::renderSelected() {
	const auto& color = button.getFillColor();
	button.setFillColor({200,0,0});
	render();
	button.setFillColor(color);
}
#include "HpBar.h"

HpBar::HpBar(float hp) :
	length(30),
	thickness(5),
	height(20),
	multiplier(length / hp),
	to_render(false)
{
	red.setSize(sf::Vector2f(length, thickness));
	red.setFillColor(sf::Color::Red);
	red.setOrigin(sf::Vector2f(length / 2, thickness / 2));

	green.setSize(sf::Vector2f(length, thickness));
	green.setFillColor(sf::Color::Green);
	green.setOrigin(sf::Vector2f(length / 2, thickness / 2));
}


void HpBar::setHp(float hp)
{
	green.setSize(sf::Vector2f(multiplier * hp, thickness));
	to_render = true;
}


void HpBar::setPosition(sf::Vector2f pos)
{
	red.setPosition(sf::Vector2f(pos.x, pos.y - height));
	green.setPosition(sf::Vector2f(pos.x, pos.y - height));
}


void HpBar::render(sf::RenderWindow& window) const
{
	if (to_render)
	{
		window.draw(red);
		window.draw(green);
	}
}
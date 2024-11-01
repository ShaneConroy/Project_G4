#include "Menu.h"

void Menu::Draw(sf::RenderWindow &window)
{
	window.draw(menuBackGround);
	window.draw(menuStartButton);
}

bool Menu::StartButtonFunction(sf::Vector2i mousePos)
{
	if (mousePos.x >= menuStartButton.getPosition().x &&
		mousePos.x <= menuStartButton.getPosition().x + menuStartButton.getGlobalBounds().width &&
		mousePos.y >= menuStartButton.getPosition().y &&
		mousePos.y <= menuStartButton.getPosition().y + menuStartButton.getGlobalBounds().height)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return true;
		}
	}
	return false;
}

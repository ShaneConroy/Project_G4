#include "Fence.h"

void Fence::UpdateGrass(sf::Color newColour)
{
	innerGrass.setFillColor(newColour);
	if (!gateOpen)
	{
		exitGrass.setFillColor(sf::Color(128, 71, 28));
	}
	else {
		exitGrass.setFillColor(newColour);
	}
}

void Fence::Draw(sf::RenderWindow& window)
{
	window.draw(fenceSquare);
	window.draw(innerGrass);
	window.draw(exitGrass);
}

void Fence::gateFunction(sf::Vector2i mousePos)
{
	clickCooldown--;
	if (clickCooldown <= 0)
	{
		if (mousePos.x >= exitGrass.getPosition().x &&
			mousePos.x <= exitGrass.getPosition().x + exitGrass.getGlobalBounds().width &&
			mousePos.y >= exitGrass.getPosition().y &&
			mousePos.y <= exitGrass.getPosition().y + exitGrass.getGlobalBounds().height)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				gateOpen = !gateOpen;
				clickCooldown = clickCooldownCap;
			}
		}
	}
}

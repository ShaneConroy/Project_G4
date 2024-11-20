#include "Fence.h"

void Fence::UpdateGrass(sf::Color newColour)
{
	innerGrass.setFillColor(newColour);
	exitGrass.setFillColor(newColour);
}

void Fence::Draw(sf::RenderWindow& window)
{
	window.draw(fenceSquare);
	window.draw(innerGrass);
	window.draw(exitGrass);
}

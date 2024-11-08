#include "Fence.h"

void Fence::Draw(sf::RenderWindow& window)
{
	window.draw(fenceSquare);
	window.draw(innerGrass);
	window.draw(exitGrass);
}

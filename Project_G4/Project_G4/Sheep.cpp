#include "Sheep.h"

void Sheep::Draw(sf::RenderWindow& window)
{
	window.draw(sheepBody);
}

// Will handle sheep finding grass nodes code
// Currently in basic version, finds closest node and goes to it
void Sheep::FindGrassNode(const std::vector<Grass>& grassNodeArray)
{
}

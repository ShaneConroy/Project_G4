#include "Sheep.h"

void Sheep::Draw(sf::RenderWindow& window)
{
	window.draw(sheepBody);
}

// Seeks towards the closest grass node
void Sheep::SeekToGrassNode()
{
	sf::Vector2f dir = closestPos - sheepBody.getPosition();
	float lenght = std::sqrt((dir.x * dir.x) + (dir.y * dir.y));

	dir = (dir / lenght) * moveSpeed;
	sheepBody.move(dir);

}

void Sheep::Update()
{
	SeekToGrassNode();
}



sf::Vector2f Sheep::randomPosition(const sf::Vector2f& vec)
{
	std::random_device random;
	std::mt19937 randomInstance(random());
	std::uniform_real_distribution<float> distX(0.f, vec.x);
	std::uniform_real_distribution<float> distY(0.f, vec.y);

	float randomX = distX(randomInstance);
	float randomY = distY(randomInstance);

	return sf::Vector2f(randomX, randomY);
}

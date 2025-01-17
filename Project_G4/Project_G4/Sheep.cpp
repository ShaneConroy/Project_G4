#include "Sheep.h"

Sheep::Sheep()
{
	sheepBody.setRadius(15);
	sheepBody.setFillColor(sf::Color::White);
	sf::Vector2f innerGrassPos = { 20.f, 544.f };
	sf::Vector2f innerGrassSize = { 1160.f, 240.f };
	sf::Vector2f spawnPos = randomPosition({ innerGrassSize.x - 30, innerGrassSize.y - 30 });
	spawnPos.x += innerGrassPos.x;
	spawnPos.y += innerGrassPos.y;

	sheepBody.setPosition(spawnPos);

	currentBehaviour = behaviours::exiting;
}

Sheep::~Sheep()
{

}

void Sheep::Draw(sf::RenderWindow& window)
{
	window.draw(sheepBody);
}

// TODO // put this into a neater behaviour class, that takes in a behavuiour
void Sheep::Update(float deltaTime, sf::RectangleShape exitFence)
{
	// If seeking, go to target
	if (currentBehaviour == behaviours::seek)
	{
		sheepBody.move(behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), closestPos));
	}
	// When leaving the pen into the field
    else if (currentBehaviour == behaviours::exiting)
    {
		// Randomise once for each sheep
        if (targetExitPosition == sf::Vector2f(0.f, 0.f))
        {
            sf::Vector2f fenceSize = exitFence.getSize();
            targetExitPosition = randomPosition({ fenceSize.x, 3.f });
            targetExitPosition.x += exitFence.getPosition().x;
            targetExitPosition.y = exitFence.getPosition().y;
        }
		// Move to exit gate
		sheepBody.move(behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), targetExitPosition));

		if (sheepBody.getGlobalBounds().intersects(exitFence.getGlobalBounds()))
		{
			currentBehaviour = behaviours::seek;
		}
    }
	// Stand still, default state
	else if (currentBehaviour == behaviours::idle)
	{
		sheepBody.move(behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), sheepBody.getPosition()));
	}
	// going back into the pen
	else if (currentBehaviour == behaviours::entering)
	{
		sheepBody.move(behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), targetExitPosition));
	}
	else if (currentBehaviour == behaviours::eating)
	{
		isEating = true;
	}

}

void Sheep::setBehaviour(behaviours behaviour)
{
	currentBehaviour = behaviour;
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



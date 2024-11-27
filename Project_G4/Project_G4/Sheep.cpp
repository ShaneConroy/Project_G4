#include "Sheep.h"

void Sheep::Draw(sf::RenderWindow& window)
{
	window.draw(sheepBody);
}

void Sheep::Update(float deltaTime, sf::RectangleShape exitFence)
{
	if (currentBehaviour == behaviours::seek)
	{
		sheepBody.move(behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), closestPos));
	}
    else if (currentBehaviour == behaviours::exiting)
    {
        if (targetExitPosition == sf::Vector2f(0.f, 0.f))
        {
            sf::Vector2f fenceSize = exitFence.getSize();
            targetExitPosition = randomPosition({ fenceSize.x, 0.f });
            targetExitPosition.x += exitFence.getPosition().x;
            targetExitPosition.y = exitFence.getPosition().y;
        }
		sheepBody.move(behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), targetExitPosition));

		if (5 >= getDistanceBetween(targetExitPosition, sheepBody.getPosition()))
		{
			currentBehaviour = behaviours::seek;
		}
    }
	else if (currentBehaviour == behaviours::idle)
	{
		sheepBody.move(behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), sheepBody.getPosition()));
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



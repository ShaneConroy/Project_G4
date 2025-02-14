#include "Behaviours.h"


// Behaviour that makes me seek towards
sf::Vector2f Behaviours::seekToTarget(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos)
{
    sf::Vector2f dir = targetPos - myPos;
    float lenght = std::sqrt((dir.x * dir.x) + (dir.y * dir.y));

    if (lenght < 5)
    {
        return { 0, 0 };
    }
    dir = (dir / lenght) * (speed * deltaTime);

    return dir;
}

// Picks a random point inside the field then walks to it. When it reaches the point, it picks another random point
sf::Vector2f Behaviours::wander(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos)
{
    float randomX = randomPositionGlobalFunc().x;
    float randomY = randomPositionGlobalFunc().y;

    sf::Vector2f dir = sf::Vector2f(randomX, randomY) - myPos;
    float length = std::sqrt((dir.x * dir.x) + (dir.y * dir.y));

    if (length < 5)
    {
        return { 0, 0 };
    }

    dir = (dir / length) * (speed * deltaTime);

    return dir;
}

sf::Vector2f Behaviours::exit(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos, sf::RectangleShape exitFence)
{

	if (targetPos == sf::Vector2f(0.f, 0.f))
	{
		sf::Vector2f fenceSize = exitFence.getSize();
		targetPos = randomPositionGlobalFunc({ fenceSize.x, 3.f });
		targetPos.x += exitFence.getPosition().x;
		targetPos.y = exitFence.getPosition().y;
	}
	// Move to exit gate
    sf::Vector2f dir = targetPos - myPos;

    return dir;
}

#include "Behaviours.h"

// Behaviour that makes me seek towards
sf::Vector2f Behaviours::seekToTarget(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos)
{
	sf::Vector2f dir = targetPos - myPos;
	float lenght = std::sqrt((dir.x * dir.x) + (dir.y * dir.y));

	if (lenght < 5)
	{
		return {0, 0};
	}
	dir = (dir / lenght) * (speed * deltaTime);

	return dir;
}

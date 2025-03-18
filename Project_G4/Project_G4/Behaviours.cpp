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
    dir = (dir / lenght) * (speed * (deltaTime * 100.f));

    return dir;
}

// Picks a random point inside the field then walks to it. When it reaches the point, it picks another random point
sf::Vector2f Behaviours::wander(float speed, float deltaTime, sf::Vector2f myPos)
{
    static sf::Vector2f wanderTarget = randomPosOnField({ 100, 1150 }, { 100, 500 });

    sf::Vector2f dir = wanderTarget - myPos;
    float length = std::sqrt((dir.x * dir.x) + (dir.y * dir.y));

    if (length < 5) // If close, pick a new target
    {
        wanderTarget = randomPosOnField({ 100, 1150 }, { 100, 500 });
    }

    dir = (dir / length) * (speed * (deltaTime * 100.f)); 


    return dir;
}

// Gives a point on the exit fence 
sf::Vector2f Behaviours::toFence(sf::RectangleShape exitFence)
{
    sf::Vector2f fenceSize = exitFence.getSize();
    sf::Vector2f targetPos = randomPosOnField({ 0.f, fenceSize.x }, { 0.f, 3.f });

    targetPos.x += exitFence.getPosition().x;
    targetPos.y = exitFence.getPosition().y;

    return targetPos;
}

sf::Vector2f Behaviours::eating(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos, float& timeToEat, bool& eating)
{
	if (timeToEat > 0)
	{
        std::cout << timeToEat << "\n";
		timeToEat -= deltaTime;
		return { 0,0 };
	}
	eating = false;
    return { 0,0 };
}

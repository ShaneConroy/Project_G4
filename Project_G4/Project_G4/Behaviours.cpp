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
    static sf::Vector2f wanderTarget = randomPosOnField({ 0.f, SCREEN_WIDTH }, { 0.f, SCREEN_HEIGHT });

    sf::Vector2f dir = wanderTarget - myPos;
    float length = std::sqrt((dir.x * dir.x) + (dir.y * dir.y));

    if (length < 5) // If close, pick a new target
    {
        wanderTarget = randomPosOnField({ 0.f, SCREEN_WIDTH }, { 0.f, SCREEN_HEIGHT });
    }

    dir = (dir / length) * (speed * (deltaTime * 100.f)); 


    return dir;
}

// Makes the sheep go towards the gate. Can be used to enter or ecit
sf::Vector2f Behaviours::toFence(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos, sf::RectangleShape exitFence)
{
    if (targetPos.x * targetPos.x + targetPos.y * targetPos.y < 25.f)
    {
        sf::Vector2f fenceSize = exitFence.getSize();
        targetPos = randomPosOnField({ 0.f, fenceSize.x }, { 0.f, 3.f });

        targetPos.x += exitFence.getPosition().x;
        targetPos.y = exitFence.getPosition().y;
    }

    sf::Vector2f dir = targetPos - myPos;
    sf::Vector2f normDir = normaliseVector(dir) * speed * deltaTime;
    return normDir;
}

// TODO // Should prolly rteurn an sf::vector2f
bool Behaviours::eating(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos, float& eatTimer, float eatTimerCap, bool& isEating, bool& doneEating)
{
    return true;
}

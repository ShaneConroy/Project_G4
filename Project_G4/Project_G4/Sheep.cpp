#include "Sheep.h"

Sheep::Sheep()
{
	sheepBody.setRadius(15);
	sheepBody.setFillColor(sf::Color::White);
	sf::Vector2f innerGrassPos = { 20.f, 544.f };
	sf::Vector2f innerGrassSize = { 1160.f, 240.f };
	sf::Vector2f spawnPos = randomPosOnField({30, innerGrassSize.x - 30}, { 30, innerGrassSize.y - 30 });
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
void Sheep::Update(float deltaTime, sf::RectangleShape exitFence, sf::RectangleShape innerGrass, std::vector<sf::Vector2f> grassPositions, std::vector<Sheep>& flock)
{
	// Flocking
	sf::Vector2f flockingForce = Separation(flock) * 15.f + Alignment(flock) * 1.0f + Cohesion(flock) * 1.0f;
	sf::Vector2f movement = behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), sheepBody.getPosition() + flockingForce);
	sheepBody.move(movement);
}

sf::Vector2f Sheep::getTargetMovement(float deltaTime, std::vector<sf::Vector2f> grassPositions, sf::RectangleShape exitFence, sf::RectangleShape innerGrass, sf::Vector2f flockingForce)
{
    sf::Vector2f movement(0.f, 0.f);

    // Add flocking force to movemnt
    movement += flockingForce;

    // If seeking, go to target
    if (currentBehaviour == behaviours::seek)
    {
        closestPos = GrassUtility::FindClosestNodePosition(sheepBody.getPosition(), grassPositions);
        movement += behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), closestPos);
    }
    // When leaving the pen into the field
    else if (currentBehaviour == behaviours::exiting)
    {
        movement += behaviour.toFence(moveSpeed, deltaTime, sheepBody.getPosition(), targetExitPosition, exitFence);
        if (exitFence.getGlobalBounds().contains(sheepBody.getPosition()))
        {
            currentBehaviour = behaviours::seek; // Switch to seeking behavior
        }
    }
    // going back into the pen
    else if (currentBehaviour == behaviours::entering)
    {
        movement += behaviour.toFence(moveSpeed, deltaTime, sheepBody.getPosition(), targetExitPosition, exitFence);
        if (exitFence.getGlobalBounds().contains(sheepBody.getPosition()))
        {
            currentBehaviour = behaviours::seek;
        }
    }
    // Stand still
    else if (currentBehaviour == behaviours::idle)
    {
        // Stay in place, no movement
        movement = { 0.f, 0.f };
    }

    if (grassPositions.empty())
    {
        if (!innerGrass.getGlobalBounds().contains(sheepBody.getPosition()))
        {
            currentBehaviour = behaviours::wander;
        }
        else if (!exitFence.getGlobalBounds().contains(sheepBody.getPosition()))
        {
            currentBehaviour = behaviours::exiting;
        }
        else {
            currentBehaviour = behaviours::wander;
        }
    }

    return movement;
}

void Sheep::setBehaviour(behaviours behaviour)
{
	currentBehaviour = behaviour;
}


// Keep them aopart
sf::Vector2f Sheep::Separation(std::vector<Sheep>& flock)
{
    sf::Vector2f steer(0.f, 0.f);
    for (Sheep& other : flock)
    {
        float distance = getDistanceBetween(getPosition(), other.getPosition());
        if (distance > 0 && distance < 50.f)
        {
            steer += (getPosition() - other.getPosition()) / distance;
        }
    }
    return steer;
}

// Move together
sf::Vector2f Sheep::Alignment(std::vector<Sheep>& flock)
{
    sf::Vector2f averageVelocity(0.f, 0.f);
    for (Sheep& other : flock)
    {
        averageVelocity += other.wanderTarget;
    }
    return averageVelocity / static_cast<float>(flock.size());
}

// Keep together
sf::Vector2f Sheep::Cohesion(std::vector<Sheep>& flock)
{
    sf::Vector2f centerMass(0.f, 0.f);
    for (Sheep& other : flock)
    {
        centerMass += other.getPosition();
    }
    return (centerMass / static_cast<float>(flock.size())) - getPosition();
}


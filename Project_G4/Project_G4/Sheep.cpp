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

void Sheep::Update(float deltaTime, sf::RectangleShape exitFence, sf::RectangleShape innerGrass, std::vector<sf::Vector2f> grassPositions, std::vector<Sheep>& flock)
{
	// Check if im the leader. Will lead other sheep
	if (isLeader)
	{

	}
	// Other sheep
	else
	{

	}
}

// Gets the sheeps veclocity
sf::Vector2f Sheep::calculateVelocity(const sf::Vector2f& previousPos, const sf::Vector2f& currentPos, float deltaTime)
{
	if (deltaTime > 0.001f) 
	{
		sf::Vector2f velocity = (currentPos - previousPos) / deltaTime;

		if (vectorLength(velocity) > maxSpeed)
		{
			velocity = normaliseVector(velocity) * maxSpeed;
		}

		return velocity;
	}
	else
	{
		return { 0.f, 0.f };
	}
}

sf::Vector2f Sheep::getLeaderDirection(std::vector<Sheep>& flock, float deltaTime)
{
	return sf::Vector2f(0.f, 0.f);
}

void Sheep::setBehaviour(behaviours behaviour)
{
	currentBehaviour = behaviour;
}


// Keep them aopart
sf::Vector2f Sheep::Separation(std::vector<Sheep>& flock)
{
	sf::Vector2f steer(0.f, 0.f);

	return steer;
}


// Move together
sf::Vector2f Sheep::Alignment(std::vector<Sheep>& flock)
{
	sf::Vector2f averageVelocity(0.f, 0.f);

	return averageVelocity;
}


// Keep together
sf::Vector2f Sheep::Cohesion(std::vector<Sheep>& flock)
{
	sf::Vector2f centerMass(0.f, 0.f);

	return centerMass;
}





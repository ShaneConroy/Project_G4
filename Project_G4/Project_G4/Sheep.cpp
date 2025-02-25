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
	sf::Vector2f movement{ 0.f, 0.f };

	if (isLeader)
	{
		movement = behaviour.wander(moveSpeed, deltaTime, sheepBody.getPosition(), wanderTarget);
	}
	else
	{
		sf::Vector2f flockingForce = Separation(flock) * 10.f + Alignment(flock) * 1.5f + Cohesion(flock) * 1.2f;
		movement = getLeaderDirection(flock, deltaTime) * 0.8f + flockingForce * 0.2f;
	}

	// Flocking
	sf::Vector2f flockingForce = Separation(flock) + Alignment(flock) + Cohesion(flock);

	velocity = flockingForce;
	sheepBody.move(velocity * deltaTime);

	velocity = calculateVelocity(sheepBody.getPosition(), previousPosition, deltaTime);
}

// Gets the sheeps veclocity
sf::Vector2f Sheep::calculateVelocity(const sf::Vector2f& previousPos, const sf::Vector2f& currentPos, float deltaTime)
{
	if (deltaTime > 0)
	{
		return (currentPos - previousPos) / deltaTime;
	}
	return { 0.f, 0.f };
}

sf::Vector2f Sheep::getLeaderDirection(std::vector<Sheep>& flock, float deltaTime)
{
    sf::Vector2f leaderDirection(0.f, 0.f);
    return leaderDirection = normaliseVector(flock[0].calculateVelocity(sheepBody.getPosition(), sheepBody.getPosition(), deltaTime));
}

void Sheep::setBehaviour(behaviours behaviour)
{
	currentBehaviour = behaviour;
}


// Keep them aopart
sf::Vector2f Sheep::Separation(std::vector<Sheep>& flock)
{
    sf::Vector2f steer(0.f, 0.f);
	int count = 0;

    for (Sheep& other : flock)
    {
        float distance = getDistanceBetween(getPosition(), other.getPosition());
        if (distance > 0 && distance < 50.f)
        {
            sf::Vector2f diff = getPosition() - other.getPosition();
            diff /= distance;
			steer += diff;
            count++;
        }
    }

	if (count > 0)
	{
		steer /= static_cast<float>(count);

        if (vectorLength(steer) > 0)
        {
			steer = normaliseVector(steer) * moveSpeed; 
        }
	}
    return steer * 10.f;
}

// Move together
sf::Vector2f Sheep::Alignment(std::vector<Sheep>& flock)
{
    sf::Vector2f averageVelocity(0.f, 0.f);
    int count = 0;

    for (Sheep& other : flock)
    {
        if (other.getPosition() != sheepBody.getPosition())
        {
			averageVelocity += other.velocity;
            count++;
        }
    }
	if (count > 0)
	{
		averageVelocity /= static_cast<float>(count);
        if (vectorLength(averageVelocity) > 0)
        {
			averageVelocity = normaliseVector(averageVelocity) * moveSpeed;
        }
	}

    return averageVelocity * 1.5f;
}

// Keep together
sf::Vector2f Sheep::Cohesion(std::vector<Sheep>& flock)
{
    sf::Vector2f centerMass(0.f, 0.f);
	int count = 0;

    for (Sheep& other : flock)
    {
        if (other.getPosition() != sheepBody.getPosition())
        {
			centerMass += other.getPosition();
			count++;
        }
    }
    if (count > 0)
    {
		centerMass /= static_cast<float>(count);
		sf::Vector2f direction = centerMass - getPosition();
        if (vectorLength(direction) > 0)
        {
			direction = normaliseVector(direction) * moveSpeed;
        }
		return direction * 1.2f;
    }

    return sf::Vector2f(0.0f, 0.0f);
}


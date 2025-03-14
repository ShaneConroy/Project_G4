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
	previousPosition = spawnPos;
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
	sf::Vector2f movementDirection(0.f, 0.f);
	previousPosition = sheepBody.getPosition();

	// Check if im the leader. Will lead other sheep
	if (isLeader)
	{
		sheepBody.setFillColor(sf::Color::Red);
		flock[0].moveSpeed = 100.f;
		movementDirection = leaderBehaviour(deltaTime, innerGrass, exitFence, flock, grassPositions);
	}
	// Other sheep
	else
	{
		sf::Vector2f seekForce = behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), flock[0].getPosition());
		sf::Vector2f separationForce = Separation(flock) * 25.f;
		sf::Vector2f alignmentForce = Alignment(flock, deltaTime) * 1.0f;
		sf::Vector2f cohesionForce = Cohesion(flock) * 2.0f;

		// Combine the forces
		movementDirection = seekForce + separationForce + alignmentForce + cohesionForce;
	}
	movementDirection = normaliseVector(movementDirection) * moveSpeed * deltaTime;
	sheepBody.move(movementDirection);
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

sf::Vector2f Sheep::getPreviousPos()
{
	return previousPosition;
}

sf::Vector2f Sheep::getLeaderDirection(std::vector<Sheep>& flock, float deltaTime)
{
	return sf::Vector2f(0.f, 0.f);
}

sf::Vector2f Sheep::getLeaderPos(std::vector<Sheep>& flock)
{
    for (const Sheep& sheep : flock)
    {
        if (sheep.isLeader)
        {
            return sheep.sheepBody.getPosition();
        }
    }
}

sf::Vector2f Sheep::leaderBehaviour(float deltaTime, sf::RectangleShape innerGrass, sf::RectangleShape exitFence, std::vector<Sheep>& flock, std::vector<sf::Vector2f> availibleGrassNodes)
{
	sf::Vector2f targetPos(0.f, 0.f);
	sf::Vector2f leaderPos = getLeaderPos(flock);

	//If the leader inside the pen
	if (innerGrass.getGlobalBounds().contains(leaderPos))
	{
		targetPos = behaviour.toFence(moveSpeed, deltaTime, leaderPos, targetPos, exitFence);
	}

	if (availibleGrassNodes.empty())
	{
		targetPos = behaviour.wander(moveSpeed, deltaTime, leaderPos);
	}
	else
	{
		sf::Vector2f closestPos = GrassUtility::FindClosestNodePosition(leaderPos, availibleGrassNodes);
		targetPos = behaviour.seekToTarget(moveSpeed, deltaTime, leaderPos, closestPos);
	}
	return targetPos;
}

void Sheep::setBehaviour(behaviours behaviour)
{
	currentBehaviour = behaviour;
}

void Sheep::availibleGrass(std::vector<sf::Vector2f> grassPositions)
{
	availibleGrassNodes = grassPositions;
}

// Keep them aopart
sf::Vector2f Sheep::Separation(std::vector<Sheep>& flock)
{
	sf::Vector2f separatingForce(0.f, 0.f);

	float desiredSeparation = 50.f;

	if (flock.size() > 0)
	{
		int count = 0;

		for (auto const& sheep : flock)
		{
			if (&sheep == this)
				continue;

			float distance = getDistanceBetween(sheepBody.getPosition(), sheep.sheepBody.getPosition());

			if (distance < desiredSeparation && distance > 0)
			{
				sf::Vector2f oppositeDirection = normaliseVector(sheepBody.getPosition() - sheep.sheepBody.getPosition());

				separatingForce += oppositeDirection / distance;
				count++;
			}
		}

		if (count > 0)
		{
			separatingForce /= static_cast<float>(count);
		}
	}

	separatingForce = normaliseVector(separatingForce);

	return separatingForce;
}

// Move together
sf::Vector2f Sheep::Alignment(std::vector<Sheep>& flock, float deltaTime)
{
	sf::Vector2f averageVelocity(0.f, 0.f);

	if (flock.size() > 0)
	{
		for (auto const& sheep : flock)
		{
			if (&sheep == this)
				continue;

			averageVelocity += this->calculateVelocity(getPreviousPos(), sheepBody.getPosition(), deltaTime);
		}

		averageVelocity /= static_cast<float>(flock.size());
	}

	return normaliseVector(averageVelocity);
}

// Keep together
sf::Vector2f Sheep::Cohesion(std::vector<Sheep>& flock)
{
	sf::Vector2f cohesionForce;

	if (flock.size() > 0)
	{
		sf::Vector2f centreOfMass;

		for (auto const& sheep : flock)
		{
			if (&sheep == this)
				continue;

			centreOfMass += sheepBody.getPosition();
		}

		centreOfMass /= static_cast<float>(flock.size()); // Get the average position

		sf::Vector2f towardsCentre = centreOfMass - sheepBody.getPosition();

		cohesionForce = normaliseVector(towardsCentre);
	}

	return cohesionForce;
}





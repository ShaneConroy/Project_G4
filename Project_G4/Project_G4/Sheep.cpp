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
void Sheep::Update(float deltaTime, sf::RectangleShape exitFence, sf::RectangleShape innerGrass, std::vector<sf::Vector2f> grassPositions, std::vector<Sheep>& flock)
{
	//// Flocking
	//sf::Vector2f flockingForce = Separation(flock) * 30.f + Alignment(flock) * 10.0f + Cohesion(flock) * 1.0f;
	//sf::Vector2f movement = behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), sheepBody.getPosition() + flockingForce);
	//sheepBody.move(movement);

	// If seeking, go to target
	if (currentBehaviour == behaviours::seek) 
	{
		closestPos = GrassUtility::FindClosestNodePosition(sheepBody.getPosition(), grassPositions);

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
	// going back into the pen
	else if (currentBehaviour == behaviours::entering)
	{
		sheepBody.move(behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), targetExitPosition));
	}
	else if (currentBehaviour == behaviours::eating)
	{
		isEating = true;

		eatTimer += deltaTime;
		if (eatTimer >= eatTimerCap)
		{
			isEating = false;
			doneEating = true;
			eatTimer = 0.0f;
			currentBehaviour = behaviours::seek;
		}
	}
	// Idle makes the sheep idly walk around the field
	else if (currentBehaviour == behaviours::idle)
	{
		wanderTimer += deltaTime;

		if (wanderTimer >= 3.0f)
		{
			if (!innerGrass.getGlobalBounds().contains(sheepBody.getPosition()))
			{
                std::random_device random;
                std::mt19937 randomInstance(random());
                std::uniform_real_distribution<float> distY(20.f, 500.f);
                std::uniform_real_distribution<float> distX(20.f, 1100.f);

                float randomX = distX(randomInstance);
                float randomY = distY(randomInstance);

                sf::Vector2f randomPoint(randomX, randomY);

				wanderTarget = randomPoint;

			}
			else {
				currentBehaviour = behaviours::exiting;
			}

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> randomWanderAdd(0.0f, 3.0f);

			wanderTimer = randomWanderAdd(gen);
		}

		sheepBody.move(behaviour.seekToTarget(moveSpeed * 0.5f, deltaTime, sheepBody.getPosition(), wanderTarget));

		// If grass appears, switch to seeking
		if (!grassPositions.empty())
		{
			currentBehaviour = behaviours::seek;
		}
	}
	else {
		currentBehaviour = behaviours::idle;
	}

	if (grassPositions.empty())
	{
		if (!innerGrass.getGlobalBounds().contains(sheepBody.getPosition()))
		{
			currentBehaviour = behaviours::idle;
		}
		else if (!exitFence.getGlobalBounds().contains(sheepBody.getPosition()))
		{
			currentBehaviour = behaviours::exiting;
		}
		else {
			currentBehaviour = behaviours::idle;
		}
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


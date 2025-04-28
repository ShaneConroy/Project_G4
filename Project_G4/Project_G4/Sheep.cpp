#include "Sheep.h"

Sheep::Sheep()
{
	sheepBody.setRadius(bodySize);
	sheepBody.setFillColor(sf::Color::White);
	sheepBody.setOrigin(sheepBody.getRadius(), sheepBody.getRadius());
	sf::Vector2f innerGrassPos = { 20.f, 544.f };
	sf::Vector2f innerGrassSize = { 1160.f, 240.f };
	sf::Vector2f spawnPos = randomPosOnField({30, innerGrassSize.x - 30}, { 30, innerGrassSize.y - 30 });
	spawnPos.x += innerGrassPos.x;
	spawnPos.y += innerGrassPos.y;
	sheepBody.setPosition(spawnPos);

	// Head
	sheepHead.setPosition(sheepBody.getPosition());
	sheepHead.setRadius(10);
	sheepHead.setFillColor(sf::Color::Black);
	sheepHead.setOrigin(sheepHead.getRadius(), sheepHead.getRadius());

	previousPosition = spawnPos;
	currentBehaviour = behaviours::exiting;
}

Sheep::~Sheep()
{
}

void Sheep::Draw(sf::RenderWindow& window)
{
	window.draw(sheepHead);
	window.draw(sheepBody);
}

void Sheep::Update(float deltaTime, sf::RectangleShape exitFence, sf::RectangleShape innerGrass, std::vector<sf::Vector2f> grassPositions, std::vector<Sheep>& flock, sf::Vector2f dogPos)
{
	sf::Vector2f movementDirection(0.f, 0.f);
	previousPosition = sheepBody.getPosition();

	// If im being eaten, dont move
	if (beingEaten)
	{
		movementDirection = sf::Vector2f(0.f, 0.f);
	}
	else {
		if (recalling)
		{
			movementDirection = handleRecall(deltaTime, exitFence, innerGrass);
		}
		else {
			// This if is here because the sheep iognore it if its somewhere else, FOR SOME REASON!!
			if (isEating)
			{
				eatTimer -= deltaTime;

				if (eatTimer <= 0.f)
				{
					doneEating = true;
					isEating = false;
					amountEaten++;
					if (amountEaten <= maxEaten)
					{
						sheepBody.setRadius(bodySize + amountEaten);

						int shade = std::max(100, 255 - (amountEaten * 20));
						sheepBody.setFillColor(sf::Color(shade, shade, shade));
					}
				}

				return;
			}

			// Check if im the leader. Will lead other sheep
			if (isLeader)
			{
				flock[0].moveSpeed = 50.f;
				movementDirection = leaderBehaviour(deltaTime, innerGrass, exitFence, flock, grassPositions);
			}
			// Other sheep
			else
			{
				sf::Vector2f seekForce = followerBehaviour(deltaTime, innerGrass, exitFence, flock, grassPositions, dogPos);

				// Problem with sheep drifting while being herded
				if (herdingTimer > 0)
				{
					movementDirection = sf::Vector2f(0.f, 0.f);
				}
				else
				{
					sf::Vector2f separationForce = Separation(flock) * 50.f;
					sf::Vector2f alignmentForce = Alignment(flock, deltaTime) * 0.8f;
					sf::Vector2f cohesionForce = Cohesion(flock) * 1.5f;

					// Combine the forces
					movementDirection = seekForce + separationForce + alignmentForce + cohesionForce;
				}
			}
		}
		movementDirection = normaliseVector(movementDirection) * moveSpeed * deltaTime;

		sf::Vector2f repulsionForce = awayFromDog(dogPos);
		movementDirection += repulsionForce;

		sheepBody.move(movementDirection);

		// This is to make the sheep head follow the body's direction
		if (vectorLength(movementDirection) > 0.01f) // If moving
		{
			sf::Vector2f direction = normaliseVector(movementDirection);
			float offsetDistance = sheepBody.getRadius() + (sheepHead.getRadius() + 20);
			sf::Vector2f targetHeadPos = sheepBody.getPosition() + direction * offsetDistance;

			float smoothing = 1.5f * deltaTime;
			sheepHead.setPosition(lerp(sheepHead.getPosition(), targetHeadPos, smoothing));
		}
		// when not moving, set the head to the body + offset
		else
		{
			sheepHead.setPosition(sheepHead.getPosition());
		}

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
	sf::Vector2f closestPos = GrassUtility::FindClosestNodePosition(getLeaderPos(flock), availibleGrassNodes);

	// If the leader inside the pen
	if (innerGrass.getGlobalBounds().contains(leaderPos))
	{
		if (!exiting)
		{
			exitTargetLeader = behaviour.toFence(exitFence); 
			exiting = true;
		}
		targetPos = behaviour.seekToTarget(moveSpeed, deltaTime, leaderPos, exitTargetLeader);
		if (getDistanceBetween(leaderPos, exitTargetLeader) < 10.f)
		{
			exitTargetLeader.y -= 20.f;
			if (getDistanceBetween(leaderPos, exitTargetLeader) < 2.f)
			{
				exiting = false;
			}
		}
	}
	else if (availibleGrassNodes.empty())
	{
		targetPos = behaviour.wander(moveSpeed, deltaTime, leaderPos);
	}
	else
	{
		targetPos = behaviour.seekToTarget(moveSpeed, deltaTime, leaderPos, closestPos);

		if (getDistanceBetween(leaderPos, targetPos) < 10.f)
		{
			availibleGrassNodes.erase(std::remove(availibleGrassNodes.begin(), availibleGrassNodes.end(), targetPos), availibleGrassNodes.end());
		}
	}
	// If sheep is close enough the grass node, begin eating
	sf::Vector2f myPos = sheepBody.getPosition();


	float distanceToGrass = getDistanceBetween(myPos, closestPos);

	if (distanceToGrass < 10.f)
	{
		if (!isEating || lastEatenGrass != closestPos)
		{
			isEating = true;
			eatTimer = 5.0f; // reset if targeting new grass node
			lastEatenGrass = closestPos;
		}

		eatTimer -= deltaTime;

		if (eatTimer <= 0.f)
		{
			doneEating = true;
			isEating = false;
		}

		return myPos;
	}
	else
	{
		isEating = false;
	}

	if (isEating)
	{
		targetPos = closestPos;
	}

	return targetPos;
}

sf::Vector2f Sheep::followerBehaviour(float deltaTime, sf::RectangleShape innerGrass, sf::RectangleShape exitFence, std::vector<Sheep>& flock, std::vector<sf::Vector2f> availibleGrassNodes, sf::Vector2f dogPos)
{
	sf::Vector2f followerTargetPos(0.f, 0.f);
	sf::Vector2f closestPos = GrassUtility::FindClosestNodePosition(sheepBody.getPosition(), availibleGrassNodes);
	sf::Vector2f leaderPos = getLeaderPos(flock);

	// Check who's inside the pen
	bool leaderInsidePen = innerGrass.getGlobalBounds().contains(leaderPos);
	bool sheepInsidePen = innerGrass.getGlobalBounds().contains(sheepBody.getPosition());

	float exitThreshold = 10.f;

	// If follower is eating, stay still until donea
	if (isEating)
	{
		eatTimer -= deltaTime;

		if (eatTimer <= 0.f)
		{
			doneEating = true;
			isEating = false;
		}

		return sheepBody.getPosition(); // Stay PUT
	}


	if (leaderInsidePen && flock[0].exiting)
	{
		followerTargetPos = behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), leaderPos);
	}

	else if (!leaderInsidePen && sheepInsidePen)
	{
		if (exitTargetLeader == sf::Vector2f(0.f, 0.f)) {
			exitTargetLeader = behaviour.toFence(exitFence);  // Set exit only once
		}

		if (getDistanceBetween(sheepBody.getPosition(), exitTargetLeader) > exitThreshold) {
			followerTargetPos = behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), exitTargetLeader);
		}
		else {
			exitTargetLeader = { 0.f, 0.f };
		}
	}
	else if (getDistanceBetween(sheepBody.getPosition(), closestPos) < 150.0f)
	{
		followerTargetPos = behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), closestPos);
	}
	else
	{
		followerTargetPos = behaviour.seekToTarget(moveSpeed, deltaTime, sheepBody.getPosition(), leaderPos);
	}

	// If sheep is getting herded
	if (herdingTimer > 0 || getDistanceBetween(sheepBody.getPosition(), dogPos) < 105.f)
	{
		if (getDistanceBetween(sheepBody.getPosition(), dogPos) < 105.f)
		{
			herdingTimer = herdingTimerCap;
		}
		else
		{
			herdingTimer -= deltaTime;
		}
	}

	// If the timer is active, the sheep movement is only influenced by the dog
	if (herdingTimer > 0)
	{
		sf::Vector2f awayFromDog = normaliseVector(sheepBody.getPosition() - dogPos);
		followerTargetPos = sheepBody.getPosition();
	}

	return followerTargetPos;
}

// Repulsion from the dog
sf::Vector2f Sheep::awayFromDog(sf::Vector2f dogPos)
{
	sf::Vector2f repulsionForce(0.f, 0.f);
	float repulsionRadius = 100.f;
	float maxRepulsion = 30.f;

	float distance = getDistanceBetween(sheepBody.getPosition(), dogPos);

	if (distance < repulsionRadius && distance > 0)
	{
		sf::Vector2f awayFromDog = normaliseVector(sheepBody.getPosition() - dogPos);
		repulsionForce = awayFromDog * (maxRepulsion * (1.0f - (distance / repulsionRadius)));
	}

	return repulsionForce;
}

void Sheep::setBehaviour(behaviours behaviour)
{
	currentBehaviour = behaviour;
}

void Sheep::availibleGrass(std::vector<sf::Vector2f> grassPositions)
{
	availibleGrassNodes = grassPositions;
}

void Sheep::setPosition(sf::Vector2f newPos)
{
	sheepBody.setPosition(newPos);
}

void Sheep::whistleHeard(float deltaTime, sf::RectangleShape exitFence, sf::RectangleShape innerGrass)
{
	recalling = true;
	exitTarget = behaviour.toFence(exitFence);
}

// Recalls the sheep to the pen
sf::Vector2f Sheep::handleRecall(float deltaTime, sf::RectangleShape exitFence, sf::RectangleShape innerGrass)
{
	sf::Vector2f myPos = sheepBody.getPosition();

	if (!reachedFence)
	{
		// Move towards the exit fence
		sf::Vector2f movement = behaviour.seekToTarget(moveSpeed, deltaTime, myPos, exitTarget);

		float distanceToFence = getDistanceBetween(myPos, exitTarget);

		if (distanceToFence < 10.f)
		{
			randomPenPos = randomPosOnField({ 40.f, 1155.f }, { 565.f, 762.f });
			reachedFence = true;
		}

		return movement;
	}
	else if (!reachedPenTarget)
	{
		// Move towards a random point inside the pen
		sf::Vector2f movement = behaviour.seekToTarget(moveSpeed, deltaTime, myPos, randomPenPos);

		float distanceToPenTarget = getDistanceBetween(myPos, randomPenPos);

		if (distanceToPenTarget < 10.f)
		{
			reachedPenTarget = true;
		}

		return movement;
	}
	else
	{
		recallTimer -= deltaTime;

		if (recallTimer <= 0.f)
		{
			recalling = false;
			reachedFence = false;
			reachedPenTarget = false;
			recallTimer = 10.f;
			exitTargetLeader = { 0.f, 0.f };
			currentBehaviour = behaviours::exiting;

		}

		// No movement while waiting
		return { 0.f, 0.f };
	}
}

// Keep them aopart
sf::Vector2f Sheep::Separation(std::vector<Sheep>& flock)
{
	sf::Vector2f separatingForce(0.f, 0.f);

	float desiredSeparation = 25.f;

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

				separatingForce += oppositeDirection / (distance * 0.5f);
				count++;
			}
		}

		if (count > 0)
		{
			separatingForce /= static_cast<float>(count);
		}
	}

	separatingForce = normaliseVector(separatingForce) * 3.0f;

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





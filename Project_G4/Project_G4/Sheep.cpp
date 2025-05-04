#include "Sheep.h"

Sheep::Sheep()
{
	// Setting up sheep's stats
	myStats = generateStats();

	int num = getNumberBetweenInt(1, 10);
	if (num == 8 || num == 9 || num == 10)
	{
		myStats.canReproduce = false;
	}
	if (num == 1 || num == 2)
	{
		myStats.deaf = true;
	}
	int G = getNumberBetweenInt(1, 100);
	if(G == 1)
		myStats.goldenSheep = true;

	// Body
	sheepBody.setRadius(myStats.bodySize);
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

	if (myStats.goldenSheep)
	{
		sheepBody.setFillColor(sf::Color(255, 215, 0));
		sheepHead.setFillColor(sf::Color(255, 215, 0));
		myStats.canReproduce = false; // Golden sheep cannot reproduce
		myStats.woolBonus = 100;
	}
}

// Constructor for the combiner
Sheep::Sheep(Sheep::sheepStats stats) : myStats(stats)
{
	// Body
	sheepBody.setRadius(myStats.bodySize);
	if (myStats.infected)
	{
		sheepBody.setFillColor(sf::Color(57, 200, 32));
		sheepHead.setFillColor(sf::Color(57, 230, 32));
	}
	else if (myStats.prestige = 1)
	{
		sheepBody.setFillColor(sf::Color(188, 230, 255)); // Blue to tell which is the new sheep
		sheepHead.setFillColor(sf::Color::Black);
	}
	//else if ()
	//{
	//	// Higher prestiges
	//}

	sheepBody.setOrigin(sheepBody.getRadius(), sheepBody.getRadius());
	sheepBody.setPosition({ 600.f, 855.f });

	// Head
	sheepHead.setRadius(10);
	sheepHead.setOrigin(sheepHead.getRadius(), sheepHead.getRadius());
	sheepHead.setPosition({ 600.f, 855.f });


	int num = getNumberBetweenInt(1, 10);
	if (num == 8 || num == 9 || num == 10)
	{
		myStats.canReproduce = false;
	}
	if (num == 1 || num == 2)
	{
		myStats.deaf = true;
	}

	previousPosition = { 600.f, 855.f };

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

void Sheep::Update(float deltaTime, sf::RectangleShape exitFence, sf::RectangleShape innerGrass, std::vector<sf::Vector2f> grassPositions, std::vector<Sheep>& flock, sf::Vector2f dogPos, sf::Vector2f wolfPos)
{
	sf::Vector2f movementDirection(0.f, 0.f);
	previousPosition = sheepBody.getPosition();
	// If im being eaten, dont move
	if (beingEaten)
	{
		movementDirection = sf::Vector2f(0.f, 0.f);
	}
	else {
		// Infected sheep only wander, nothing else // TODO FIX
		if (myStats.infected)
		{

		}

		if (whistleDelay > 0.f) // Being deaf is handled in world
		{
			whistleDelay -= deltaTime;

			if (whistleDelay <= 0.f)
			{
				whistleHeard(deltaTime, exitFence, innerGrass);
				whistleDelay = -1.f; // reset
			}
		}

		if (recalling)
		{
			movementDirection = handleRecall(deltaTime, exitFence, innerGrass);
		}
		else {
			// This if is here because the sheep iognore it if its somewhere else, FOR SOME REASON!!
			if (isEating)
			{
				myStats.eatSpeed -= deltaTime;

				if (myStats.eatSpeed <= 0.f)
				{
					doneEating = true;
					isEating = false;
					amountEaten++;
					myStats.greatness += 1; // Increase greatness after eating
					if (amountEaten <= maxEaten)
					{
						sheepBody.setRadius(myStats.bodySize + amountEaten);

						if (!myStats.goldenSheep && !myStats.infected)
						{
							if (myStats.prestige == 0) // White sheep.
							{
								int shade = std::max(100, 255 - (amountEaten * 20));
								sheepBody.setFillColor(sf::Color(shade, shade, shade));
							}
							else if (myStats.prestige == 1) // Blue sheep.
							{
								float blend = std::clamp(static_cast<float>(amountEaten) / maxEaten, 0.f, 1.f);

								int r = static_cast<int>(188 + blend * (1 - 188));
								int g = static_cast<int>(230 + blend * (92 - 230));
								int b = static_cast<int>(255 + blend * (146 - 255));

								sf::Color stepColor(
									std::clamp(r, 0, 255),
									std::clamp(g, 0, 255),
									std::clamp(b, 0, 255)
								);

								sheepBody.setFillColor(stepColor);
							}
						}
					}
				}

				return;
			}

			// Check if im the leader. Will lead other sheep
			if (isLeader)
			{
				flock[0].myStats.walkSpeed = 50.f;
				//myStats.walkSpeed = myStats.walkSpeed + 50.f; // TODO // Fix. Leaders should be faster
				movementDirection = leaderBehaviour(deltaTime, innerGrass, exitFence, flock, grassPositions);
				leadTimer += deltaTime;
				if (leadTimer >= 2.f)
				{
					myStats.greatness += 1; // Increase greatness after leading for a bit
					leadTimer = 0.f;
				}
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

		// Fleeing from wolf
		if (getDistanceBetween(getPosition(), wolfPos) < myStats.fear)
		{
			sf::Vector2f fleeForce = normaliseVector(getPosition() - wolfPos) * 50.f;
			movementDirection += fleeForce;
		}

		movementDirection = normaliseVector(movementDirection) * myStats.walkSpeed * deltaTime;

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

		// Every 10 seconds, add 1 to greatness
		myStats.timeAlive += deltaTime;
		if (myStats.timeAlive >= 10.f)
		{
			myStats.greatness += 1;
			myStats.timeAlive = 0.f;
		}

		if (myStats.infected)
		{
			infectedTTL -= deltaTime;
			if (infectedTTL <= 0.0f)
			{
				eatenByWolf = true; // Reusing bc its easiest
			}
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

	if (myStats.infected)
	{
		return targetPos = behaviour.wander(myStats.walkSpeed, deltaTime, leaderPos);
	}

	// If the leader inside the pen
	if (innerGrass.getGlobalBounds().contains(leaderPos))
	{
		if (!exiting)
		{
			exitTargetLeader = behaviour.toFence(exitFence); 
			exiting = true;
		}
		targetPos = behaviour.seekToTarget(myStats.walkSpeed, deltaTime, leaderPos, exitTargetLeader);
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
		targetPos = behaviour.wander(myStats.walkSpeed, deltaTime, leaderPos);
	}
	else
	{
		targetPos = behaviour.seekToTarget(myStats.walkSpeed, deltaTime, leaderPos, closestPos);

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
			myStats.eatSpeed = 5.0f; // reset if targeting new grass node
			lastEatenGrass = closestPos;
		}

		myStats.eatSpeed -= deltaTime;

		if (myStats.eatSpeed <= 0.f)
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

	if (myStats.infected)
	{
		return followerTargetPos = behaviour.wander(myStats.walkSpeed, deltaTime, sheepBody.getPosition());
	}

	// If follower is eating, stay still until donea
	if (isEating)
	{
		myStats.eatSpeed -= deltaTime;

		if (myStats.eatSpeed <= 0.f)
		{
			doneEating = true;
			isEating = false;
		}

		return sheepBody.getPosition(); // Stay PUT
	}


	if (leaderInsidePen && flock[0].exiting)
	{
		followerTargetPos = behaviour.seekToTarget(myStats.walkSpeed, deltaTime, sheepBody.getPosition(), leaderPos);
	}

	else if (!leaderInsidePen && sheepInsidePen)
	{
		if (exitTargetLeader == sf::Vector2f(0.f, 0.f)) {
			exitTargetLeader = behaviour.toFence(exitFence);  // Set exit only once
		}

		if (getDistanceBetween(sheepBody.getPosition(), exitTargetLeader) > exitThreshold) {
			followerTargetPos = behaviour.seekToTarget(myStats.walkSpeed, deltaTime, sheepBody.getPosition(), exitTargetLeader);
		}
		else {
			exitTargetLeader = { 0.f, 0.f };
		}
	}
	else if (getDistanceBetween(sheepBody.getPosition(), closestPos) < 150.0f)
	{
		followerTargetPos = behaviour.seekToTarget(myStats.walkSpeed, deltaTime, sheepBody.getPosition(), closestPos);
	}
	else
	{
		followerTargetPos = behaviour.seekToTarget(myStats.walkSpeed, deltaTime, sheepBody.getPosition(), leaderPos);
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
		sf::Vector2f movement = behaviour.seekToTarget(myStats.walkSpeed, deltaTime, myPos, exitTarget);

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
		sf::Vector2f movement = behaviour.seekToTarget(myStats.walkSpeed, deltaTime, myPos, randomPenPos);

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

// Generates random stats for the sheep
Sheep::sheepStats Sheep::generateStats()
{
	Sheep::sheepStats stats;

	// These will always be defaluted to 0
	stats.greatness = 0;
	stats.timeAlive = 0.f;
	stats.timeCLoseToWolf = 0.f;

	int howMuchBuffs = getNumberBetweenInt(0, 2);
	int howMuchDebuffs = getNumberBetweenInt(0, 2);

	for (int iter = 0; iter < howMuchBuffs; iter++)
	{
		int statsToBuff = getNumberBetweenInt(0, 5);
		switch (statsToBuff)
		{
		case 0:
			stats.walkSpeed += getNumberBetweenInt(1, 25);
			break;
		case 1:
			stats.eatSpeed += getNumberBetweenFloat(1.0f, 5.0f);
			break;
		case 2:
			stats.woolBonus += getNumberBetweenInt(10, 100);
			break;
		case 3:
			stats.bodySize += getNumberBetweenInt(1, 10);
			break;
		case 4:
			stats.awarness -= getNumberBetweenFloat(0.0f, 2.0f);
			break;
		case 5:
			stats.fear += getNumberBetweenInt(10, 100);
			break;
		default:
			break;
		}
	}

	for (int iter = 0; iter < howMuchDebuffs; iter++)
	{
		int statsToDebuff = getNumberBetweenInt(0, 5);
		{
			switch (statsToDebuff)
			{
			case 0:
				stats.walkSpeed -= getNumberBetweenInt(1, 25);
				break;
			case 1:
				stats.eatSpeed -= getNumberBetweenFloat(1.0f, 5.0f);
				break;
			case 2:
				stats.woolBonus -= getNumberBetweenInt(10, 100);
				break;
			case 3:
				stats.bodySize -= getNumberBetweenInt(1, 5);
				break;
			case 4:
				stats.awarness += getNumberBetweenFloat(0.0f, 2.0f);
				break;
			case 5:
				stats.fear -= getNumberBetweenInt(10, 100);
				break;
			default:
				break;
			}
		}
	}

	return stats;
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





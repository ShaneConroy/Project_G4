#include "Wolf.h"


Wolf::Wolf(int spawnLocale)
{

	wolfBody.setRadius(25);
	wolfBody.setFillColor(sf::Color(138, 43, 226));
	spawnWolf(spawnLocale);
	targetSheep = nullptr;
}

void Wolf::Draw(sf::RenderWindow& window)
{
	window.draw(wolfBody);
}

// Updates the wolf's state to hunt the closest sheep
void Wolf::Hunt(std::vector<Sheep*>& flock, float deltaTime)
{
    position = wolfBody.getPosition();

    if (stunTimer > 0.f)
    {
        stunTimer -= deltaTime;
        return;
    }

    if (!targetSheep && !flock.empty())
    {
        targetSheep = FindClosestSheep(flock);
    }

    if (targetSheep)
    {
        sf::Vector2f direction = normaliseVector(targetSheep->getPosition() - wolfBody.getPosition());
        wolfBody.move(direction * 80.f * deltaTime);

        float dist = getDistanceBetween(wolfBody.getPosition(), targetSheep->getPosition());
        if (dist < 10.f)
        {
            isEating = true;
            targetSheep->beingEaten = true;
        }
    }

    if (isEating && targetSheep)
    {
        eatTimer -= deltaTime;

		std::cout << eatTimer << std::endl;

        if (eatTimer <= 0.f)
        {
            targetSheep->eatenByWolf = true;
            targetSheep->beingEaten = false;
            targetSheep = nullptr;
            isEating = false;
            eatTimer = eatDuration;
        }
        return;
    }

}

// Based off spawnPos, spawns on one edge
void Wolf::spawnWolf(int spawnPos)
{
	if (spawnPos == 0)
	{
        wolfBody.setPosition((SCREEN_WIDTH / 2) - 12.5, 0.f);
		position = wolfBody.getPosition();
	}
	else if (spawnPos == 1)
	{
        wolfBody.setPosition(0, (SCREEN_HEIGHT / 2) - 12.5);
		position = wolfBody.getPosition();
	}
	else if (spawnPos == 2)
	{
		wolfBody.setPosition((SCREEN_WIDTH) - 12.5, (SCREEN_HEIGHT / 2) - 12.5);
		position = wolfBody.getPosition();
	}

    position = wolfBody.getPosition();
}

// This will find the closest sheep to the wolf
Sheep* Wolf::FindClosestSheep(std::vector<Sheep*>& flock)
{
    Sheep* closest = nullptr;
    float minDistance = 9999999; // Arbitrary large number

    if (!flock.empty())
    {
        for (Sheep* sheep : flock)
        {
            // Loop through alll sheep
            float distance = getDistanceBetween(position, sheep->getPosition());
            if (distance < minDistance)
            {
                minDistance = distance;
                closest = sheep;
            }
        }
    }
    
    return closest;
}

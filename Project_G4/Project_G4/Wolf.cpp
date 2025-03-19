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

// Returns a pointer to the closest sheep
void Wolf::Hunt(std::vector<Sheep*>& flock, float deltaTime)
{
    // If no target, find onme
    if (targetSheep == nullptr)
    {
        targetSheep = FindClosestSheep(flock);
    }

    if (targetSheep)
    {
        sf::Vector2f wolfPos = wolfBody.getPosition();
        sf::Vector2f direction = normaliseVector(targetSheep->getPosition() - wolfPos);

        wolfBody.move(direction * 80.f * deltaTime);

        // Eat
        if (getDistanceBetween(position, targetSheep->getPosition()) < 10.f)
        {
			/*std::cout << getDistanceBetween(position, targetSheep->getPosition()) << "\n";*/
            // TODO // Make eat behaviour
            //targetSheep = nullptr;  // Reset target after catching
        }
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
}

// This will find the closest sheep to the wolf
Sheep* Wolf::FindClosestSheep(std::vector<Sheep*>& flock)
{
    Sheep* closest = nullptr;
    float minDistance = 9999999; // Arbitrary large number

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

    return closest;
}

#include "Wolf.h"
#include "World.h"

Wolf::Wolf(int spawnLocale)
{
	wolfBody.setRadius(25);
	wolfBody.setFillColor(sf::Color(125, 125, 125));
    wolfBody.setOrigin(wolfBody.getRadius(), wolfBody.getRadius());
	spawnWolf(spawnLocale);
	targetSheep = nullptr;

	wolfHead.setPosition(wolfBody.getPosition());
	wolfHead.setRadius(18);
	wolfHead.setFillColor(sf::Color(125, 125, 125));
	wolfHead.setOrigin(wolfHead.getRadius(), wolfHead.getRadius());

    wolfTail.setPointCount(4);
    wolfTail.setPoint(0, sf::Vector2f(1.5f, -15.f));  // Top center
    wolfTail.setPoint(1, sf::Vector2f(30.f, 0.f));   // Right tip
    wolfTail.setPoint(2, sf::Vector2f(1.5f, 15.f));   // Bottom center
    wolfTail.setPoint(3, sf::Vector2f(-20.f, 0.f));  // Left tip
    wolfTail.setFillColor(sf::Color(125, 125, 125));
    wolfTail.setPosition(wolfBody.getPosition());

    wolfEars.setPointCount(4);
	wolfEars.setPoint(0, sf::Vector2f(10.f, 0.f)); // in point
	wolfEars.setPoint(1, sf::Vector2f(-7.5f, 30.f)); // top ear
    wolfEars.setPoint(2, sf::Vector2f(-5.f, 0.f)); // in point back
	wolfEars.setPoint(3, sf::Vector2f(-7.5f, -30.f)); // down ear
	wolfEars.setFillColor(sf::Color(125, 125, 125));
	wolfEars.setPosition(wolfHead.getPosition());

    wolfSnout.setPointCount(6);
    wolfSnout.setPoint(0, sf::Vector2f(0.f, 10.f));
    wolfSnout.setPoint(1, sf::Vector2f(-30.f, 10.f));
    wolfSnout.setPoint(2, sf::Vector2f(-30.f, -10.f));
    wolfSnout.setPoint(3, sf::Vector2f(0.f, -10.f));
    wolfSnout.setPoint(4, sf::Vector2f(5.f, -5.f));
    wolfSnout.setPoint(5, sf::Vector2f(5.f, 5.f));

    wolfSnout.setFillColor(sf::Color(125, 125, 125));
    wolfSnout.setPosition(wolfHead.getPosition());

}

void Wolf::Draw(sf::RenderWindow& window)
{
    window.draw(wolfTail);
	window.draw(wolfHead);
	window.draw(wolfBody);
	window.draw(wolfEars);
	window.draw(wolfSnout);
}

// Updates the wolf's state to hunt the closest sheep
void Wolf::Hunt(std::vector<Sheep*>& flock, float deltaTime, sf::RectangleShape innerGrass, World* world) //Next
{
    position = wolfBody.getPosition();

    if (stunTimer > 0.f)
    {
        stunTimer -= deltaTime;
        return;
    }

    if (!targetSheep && !flock.empty())
    {
        targetSheep = FindClosestSheep(flock, innerGrass);
    }

    if (targetSheep)
    {
        sf::Vector2f direction = normaliseVector(targetSheep->getPosition() - wolfBody.getPosition());
        wolfBody.move(direction * 80.f * deltaTime);

        // For updating the wolf's body parts
        if (vectorLength(direction) > 0.01f)
        {
            float offsetDistance = wolfBody.getRadius() + (wolfHead.getRadius() - 3);
            sf::Vector2f targetHeadPos = wolfBody.getPosition() + normaliseVector(direction) * offsetDistance;

            float smoothing = 10.f * deltaTime;
            wolfHead.setPosition(lerp(wolfHead.getPosition(), targetHeadPos, smoothing));

            wolfEars.setPosition(wolfHead.getPosition());

            float headAngle = atan2(direction.y, direction.x) * 180 / 3.14159f;
            wolfEars.setRotation(headAngle);

            float snoutOffsetDistance = wolfHead.getRadius() + 7.5;
            sf::Vector2f snoutOffset = normaliseVector(direction) * snoutOffsetDistance;

            wolfSnout.setPosition(wolfHead.getPosition() + snoutOffset);

            float snoutAngle = atan2(direction.y, direction.x) * 180 / 3.14159f;
            wolfSnout.setRotation(snoutAngle);

            // The wolfs tail
            float tailOffsetDistance = wolfBody.getRadius() + 10.f;
            sf::Vector2f tailOffset = -normaliseVector(direction) * tailOffsetDistance;

            float tailSmoothing = 10.f * deltaTime;
            wolfTail.setPosition(lerp(wolfTail.getPosition(), wolfBody.getPosition() + tailOffset, tailSmoothing));

            float tailAngle = atan2(direction.y, direction.x) * 180 / 3.14159f;
            wolfTail.setRotation(tailAngle + 180.f);

        }

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

        if (eatTimer <= 0.f)
        {
            targetSheep->eatenByWolf = true;
            targetSheep->beingEaten = false;
            if (targetSheep->myStats.infected == true) // If wolf ate an infected sheep. Wolf dies and drops cash orb
            {
                // Cash orb particle
                WoolParticle cashOrb;
                cashOrb.shape.setRadius(12.f);
                cashOrb.shape.setFillColor(sf::Color(242, 43, 110));
                cashOrb.shape.setPosition(wolfBody.getPosition());
                cashOrb.sourceSheep = targetSheep; // Reuse for bonus calc

                float angle = static_cast<float>((rand() % 360) * (3.14159 / 180.f));
                float speed = static_cast<float>((rand() % 30) + 50);
                cashOrb.velocity = { cos(angle) * speed, sin(angle) * speed };

                world->spawnCashOrb(cashOrb);

                isWolfDead = true;
            }
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
Sheep* Wolf::FindClosestSheep(std::vector<Sheep*>& flock, sf::RectangleShape innerGrass)
{
    Sheep* closest = nullptr;
    float minDistance = 9999999; // Arbitrary large number

    if (!flock.empty())
    {
        for (Sheep* sheep : flock)
        {
            if (sheep->inPen(innerGrass))
            {
                continue;
            }

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

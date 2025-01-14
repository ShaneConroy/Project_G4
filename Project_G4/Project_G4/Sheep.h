#pragma once
#include "Global.h"
#include "Behaviours.h"
#include "Behaviours_Enum.h"

// Sheep should control rotation, position, speed,
//	behaviours such as eating grass, seeking grass or should it?
//	It should have specific requirments then itll call on a behaviour class based off that.

class Sheep
{
public:

	Sheep()
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

	~Sheep()
	{
	}

	void Draw(sf::RenderWindow& window);
	template <typename T>
	float FindGrassNode(const std::vector<T>& grassNodeArray);
	void Update(float, sf::RectangleShape);

	sf::Vector2f getPosition() { return sheepBody.getPosition(); };
	float getRadius() { return sheepBody.getRadius(); };

	void setBehaviour(behaviours);

	sf::CircleShape getCirc() { return sheepBody; };

private:

	behaviours currentBehaviour;
	Behaviours behaviour;
	
	sf::Vector2f closestPos;
	sf::CircleShape sheepBody;

	float moveSpeed = 50.0f;

	sf::Vector2f randomPosition(const sf::Vector2f& vec);
	sf::Vector2f targetExitPosition;
};

// Takes in an array of grass nodes, loops through and finds the closest
template<typename T>
inline float Sheep::FindGrassNode(const std::vector<T>& grassNodeArray)
{
	float currentClosest = FLT_MAX;
	float newClosest;

	for (int iter = 0; iter < grassNodeArray.size(); iter++)
	{
		newClosest = getDistanceBetween(sheepBody.getPosition(), grassNodeArray[iter].getPosition());
		if (newClosest < 5)
		{
			currentBehaviour = behaviours::idle; // TODO // eat
		}
		if (newClosest < currentClosest)
		{
			currentClosest = newClosest;
			closestPos = grassNodeArray[iter].getPosition();
		}
	}
	return currentClosest;
}

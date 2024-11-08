#pragma once
#include "Global.h"

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
		sf::Vector2f spawnPos = randomPosition({ SCREEN_WIDTH - 30, (SCREEN_HEIGHT * 2 / 3)});
		sheepBody.setPosition(spawnPos);
	}

	~Sheep()
	{
	}

	void Draw(sf::RenderWindow& window);
	template <typename T>
	float FindGrassNode(const std::vector<T>& grassNodeArray);
	void SeekToGrassNode();
	void Update();

private:

	sf::Vector2f closestPos;
	sf::CircleShape sheepBody;

	float moveSpeed = 1.0f;

	sf::Vector2f randomPosition(const sf::Vector2f& vec);

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
		if (newClosest < currentClosest)
		{
			currentClosest = newClosest;
			closestPos = grassNodeArray[iter].getPosition();
		}
	}
	return currentClosest;
}

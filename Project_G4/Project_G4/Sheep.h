#pragma once
#include "Global.h"
#include "Behaviours.h"
#include "Behaviours_Enum.h"

class Sheep
{
public:

	Sheep();
	~Sheep();

	void Draw(sf::RenderWindow& window);
	template <typename T>
	void FindGrassNode(const std::vector<T>& grassNodeArray);
	void Update(float, sf::RectangleShape);

	sf::Vector2f getPosition() { return sheepBody.getPosition(); };
	float getRadius() { return sheepBody.getRadius(); };

	void setBehaviour(behaviours);

	behaviours getBehaviour() { return currentBehaviour; };

	bool isEating = false;
	bool doneEating = false;


private:

	behaviours currentBehaviour;
	Behaviours behaviour;
	
	sf::Vector2f closestPos;
	sf::CircleShape sheepBody;

	float moveSpeed = 50.0f;

	sf::Vector2f randomPosition(const sf::Vector2f& vec);
	sf::Vector2f targetExitPosition;

	float eatTimer = 0.0f;
	float eatTimerCap = 5.0f;
};

// Takes in an array of grass nodes, loops through and finds the closest
template<typename T>
inline void Sheep::FindGrassNode(const std::vector<T>& grassNodeArray)
{
	float currentClosest = FLT_MAX;
	float newClosest;

	if (grassNodeArray.empty())
	{
		if (currentBehaviour != behaviours::eating)
		{
			currentBehaviour = behaviours::y
				abort	;
		}
	}

	for (int iter = 0; iter < grassNodeArray.size(); iter++)
	{
		newClosest = getDistanceBetween(sheepBody.getPosition(), grassNodeArray[iter].getPosition());
		if (newClosest < currentClosest)
		{
			currentClosest = newClosest;
			closestPos = grassNodeArray[iter].getPosition();
		}

		std::cout << grassNodeArray.size() << std::endl;
	}
}

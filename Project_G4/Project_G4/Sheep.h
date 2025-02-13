#pragma once
#include "Global.h"
#include "Behaviours.h"
#include "Behaviours_Enum.h"
#include "GrassUtility.h"

class Sheep
{
public:

	Sheep();
	~Sheep();

	GrassUtility grassUtility;

	void Draw(sf::RenderWindow& window);

	void Update(float deltaTime, sf::RectangleShape exitFence, sf::RectangleShape innerGrass, std::vector<sf::Vector2f> grassPositions, std::vector<Sheep>& flock);

	sf::Vector2f getPosition() { return sheepBody.getPosition(); };
	float getRadius() { return sheepBody.getRadius(); };

	void setBehaviour(behaviours);

	behaviours getBehaviour() { return currentBehaviour; };

	sf::FloatRect getBody() { return sheepBody.getGlobalBounds(); };

	bool isEating = false;
	bool doneEating = false;


private:

	behaviours currentBehaviour;
	Behaviours behaviour;
	
	sf::Vector2f closestPos;
	sf::CircleShape sheepBody;

	float moveSpeed = 50.0f;

	sf::Vector2f randomPosition(const sf::Vector2f& vec);
	sf::Vector2f targetExitPosition = { 0.f,0.f };

	float eatTimer = 0.0f;
	float eatTimerCap = 5.0f;

	float wanderTimer = 3.0f;
	sf::Vector2f wanderTarget;

	sf::Vector2f Separation(std::vector<Sheep>& flock);
	sf::Vector2f Alignment(std::vector<Sheep>& flock);
	sf::Vector2f Cohesion(std::vector<Sheep>& flock);
};

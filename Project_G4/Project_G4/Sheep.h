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
	bool isLeader = false;

private:

	behaviours currentBehaviour;
	Behaviours behaviour;

	sf::CircleShape sheepBody;

	float moveSpeed = 35.0f;
	float maxSpeed = 200.f;
	float eatTimer = 0.0f;
	float eatTimerCap = 5.0f;
	float wanderTimer = 3.0f;

	sf::Vector2f targetExitPosition = { 0.f,0.f };
	sf::Vector2f closestPos;
	sf::Vector2f wanderTarget{ 500.f, 500.f };
	sf::Vector2f previousPosition;
	sf::Vector2f velocity;

	sf::Vector2f Separation(std::vector<Sheep>& flock);
	sf::Vector2f Alignment(std::vector<Sheep>& flock);
	sf::Vector2f Cohesion(std::vector<Sheep>& flock);

	sf::Vector2f calculateVelocity(const sf::Vector2f& previousPos, const sf::Vector2f& currentPos, float deltaTime);
	sf::Vector2f getLeaderDirection(std::vector<Sheep>& flock, float deltaTime);

};

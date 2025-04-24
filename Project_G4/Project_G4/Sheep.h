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
	void Update(float deltaTime, sf::RectangleShape exitFence, sf::RectangleShape innerGrass, std::vector<sf::Vector2f> grassPositions, std::vector<Sheep>& flock, sf::Vector2f dogPos);
	void setBehaviour(behaviours);
	void availibleGrass(std::vector<sf::Vector2f> grassPositions);
	void setRadius(float r) { sheepBody.setRadius(r); }
	void setColour(sf::Color c) { sheepBody.setFillColor(c); }

	float getRadius() { return sheepBody.getRadius(); };
	float eatTimer = 5.0f;

	int amountEaten = 0; // This is used to change the sheeps current wool stage

	behaviours getBehaviour() { return currentBehaviour; };

	sf::Vector2f getPosition() { return sheepBody.getPosition(); };
	sf::FloatRect getBody() { return sheepBody.getGlobalBounds(); };
	sf::Vector2f lastEatenGrass;

	void setPosition(sf::Vector2f newPos);

	bool isEating = false;
	bool doneEating = false;
	bool isLeader = false;

private:

	behaviours currentBehaviour;
	Behaviours behaviour;

	sf::CircleShape sheepBody;

	float moveSpeed = 35.0f;
	float maxSpeed = 200.f;

	float wanderTimer = 3.0f;
	float herdingTimer = 0.0f;
	float herdingTimerCap = 0.5f;

	bool exiting = false;

	int maxEaten = 7; // Dont make them too fat
	int bodySize = 15;

	std::vector<sf::Vector2f> availibleGrassNodes;

	sf::Vector2f targetExitPosition = { 0.f,0.f };
	sf::Vector2f closestPos;
	sf::Vector2f wanderTarget{ 500.f, 500.f };
	sf::Vector2f previousPosition;
	sf::Vector2f velocity;
	sf::Vector2f exitTarget;

	sf::Vector2f Separation(std::vector<Sheep>& flock);
	sf::Vector2f Alignment(std::vector<Sheep>& flock, float deltaTime);
	sf::Vector2f Cohesion(std::vector<Sheep>& flock);

	sf::Vector2f calculateVelocity(const sf::Vector2f& previousPos, const sf::Vector2f& currentPos, float deltaTime);
	sf::Vector2f getPreviousPos();

	sf::Vector2f getLeaderDirection(std::vector<Sheep>& flock, float deltaTime);
	sf::Vector2f getLeaderPos(std::vector<Sheep>& flock);

	sf::Vector2f leaderBehaviour(float deltaTime, sf::RectangleShape innerGrass, sf::RectangleShape exitFence, std::vector<Sheep>&, std::vector<sf::Vector2f> availibleGrassNodes);
	sf::Vector2f followerBehaviour(float deltaTime, sf::RectangleShape innerGrass, sf::RectangleShape exitFence, std::vector<Sheep>&, std::vector<sf::Vector2f> availibleGrassNodes, sf::Vector2f dogPos);

	sf::Vector2f awayFromDog(sf::Vector2f dogPos);
};

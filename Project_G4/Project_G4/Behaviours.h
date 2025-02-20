#pragma once

#include "Global.h"

class Behaviours
{
public:

	sf::Vector2f seekToTarget(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos);
	sf::Vector2f wander(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos);
	sf::Vector2f toFence(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos, sf::RectangleShape exitFence);
	bool eating(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos, float& eatTimer, float eatTimerCap, bool& isEating, bool& doneEating);
};
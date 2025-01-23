#pragma once

#include "Global.h"

class Behaviours
{
private:

public:
	sf::Vector2f seekToTarget(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos);
	sf::Vector2f wander(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos);
};


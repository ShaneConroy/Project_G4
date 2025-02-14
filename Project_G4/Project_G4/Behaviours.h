#pragma once

#include "Global.h"

class Entity;

class Behaviours
{
public:

	sf::Vector2f seekToTarget(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos);
	sf::Vector2f wander(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos);
	sf::Vector2f exit(float speed, float deltaTime, sf::Vector2f myPos, sf::Vector2f targetPos, sf::RectangleShape exitFence);
};
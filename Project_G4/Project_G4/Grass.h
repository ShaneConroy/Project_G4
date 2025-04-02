#pragma once
#include "Global.h"

class Grass
{
public:
	Grass()
	{
		grassNode.setFillColor(sf::Color(138, 225, 6));
		grassNode.setRadius(7);
		sf::Vector2f spawnPos = randomPosOnField({ 100, 1150 }, { 100, 500 });
		grassNode.setPosition(spawnPos);
		
	}
	~Grass()
	{
	}
	sf::CircleShape grassNode;
	sf::Vector2f getPosition() const { return grassNode.getPosition(); }
	bool CheckTaken() { return taken; };
	bool CheckEaten() { return eaten; };
	void UpdateTaken(bool);
	void UpdateEaten(bool);

private:

	bool taken = false; // will check if the current grass node is avaiable or nah
	bool eaten = false; // will check if the current grass node is eaten or nah	
};


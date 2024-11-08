#pragma once
#include "Global.h"
#include "Grass.h"

// Sheep should control rotation, position, speed,
//	behaviours such as eating grass, seeking grass or should it?
//	It should have specific requirments then itll call on a behaviour class based off that.

class Sheep
{
public:

	Sheep()
	{
		sf::CircleShape sheepBody;
		sheepBody.setRadius(15);
		sheepBody.setFillColor(sf::Color::White);
		sheepBody.setPosition(100, 100);
	}

	~Sheep()
	{

	}

	void Draw(sf::RenderWindow& window);
	void FindGrassNode(const std::vector<Grass>& grassNodeArray);

private:

	sf::Sprite sheepBody;
	sf::Texture sheepTexture;

};


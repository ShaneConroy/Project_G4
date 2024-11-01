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

	}

	~Sheep()
	{

	}

private:

	sf::Sprite sheepBody;
	sf::Texture sheepTexture;


};


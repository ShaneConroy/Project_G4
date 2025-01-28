#pragma once
#include "Global.h"
#include "Grass.h"
#include "Fence.h"
#include "Sheep.h"
#include "Economy.h"
#include "Funds_Enum.h"

// The world will control the fence, maybe spawning of grass nodes, day/night cycle

// Currently the dyalight cycle goes from light green (day) to night but doesnt go back to day.
// A solution to this could be having a button "Next day?" And when you press it, it resets to day

// Day -> (134, 172, 19)
// Night -> (40, 108, 89)

class World
{
private:

	float transition = 0.0f;
	
	Grass grassNode;
	std::vector<Grass> grassNodeArray;
	const int GRASS_CAP = 30;
	void SpawnGrassNodes();
	std::vector<sf::Vector2f> UpdateGrassNodes();

	Fence fence;
	void updateFencedGrass();

	Sheep sheep;
	std::vector<Sheep> sheepArray;
	void PopulateWorldWithSheep();
	
	int currentTime = 0;
	sf::RectangleShape bg;

	bool isDay = true;

	Economy econ;

public:
	int WorldTime();
	sf::Color DaylightCycle();
	void Draw(sf::RenderWindow& window);
	void PassGrassToSheep();
	void Update(float, sf::Vector2i);
	void FixedUpdate();
	World()
	{
		bg.setSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
	}
	~World()
	{

	}
};


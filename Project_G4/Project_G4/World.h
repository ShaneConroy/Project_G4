#pragma once
#include "Global.h"
#include "Grass.h"
#include "Fence.h"
#include "Sheep.h"
#include "Economy.h"
#include "Funds_Enum.h"
#include "Wolf.h"

// The world will control the fence, maybe spawning of grass nodes, day/night cycle

// Currently the dyalight cycle goes from light green (day) to night but doesnt go back to day.
// A solution to this could be having a button "Next day?" And when you press it, it resets to day

// Day -> (134, 172, 19)
// Night -> (40, 108, 89)

class World
{
private:

	Grass grassNode;
	Economy econ;
	Sheep sheep;
	Fence fence;
	Wolf wolf;

	sf::RectangleShape bg;

	std::vector<sf::Vector2f> UpdateGrassNodes();

	void SpawnGrassNodes();
	void updateFencedGrass();
	void PopulateWorldWithSheep();
	void spawnWolf();

	void up_SheepMax();
	void up_WoolSell();
	void up_SheepAmount();
	void up_GrassAmount();

	float transition = 0.0f;

	bool isDay = true;

	const int GRASS_CAP = 30;
	const int timeInDay = 3334;
	int currentTime = 0;
	int grassBuyAmount = 1;
	int sheepCap = 5;
	int eatTimer = 480; // Arbutary number, make sure maybe fix?
	int eatTimerCap = 480;

	std::vector<Sheep> sheepArray;
	std::vector<Grass> grassNodeArray;
	std::vector<Sheep*> herd;

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
		econ.setUpUpgradeMaps();
	}
	~World()
	{

	}
};


#pragma once
#include "Global.h"
#include "Grass.h"
#include "Fence.h"
#include "Sheep.h"
#include "Economy.h"
#include "Funds_Enum.h"
#include "Wolf.h"
#include "Dog.h"

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
	Dog dog;

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

	void shearsFunc(sf::Vector2i mousePos);

	float transition = 0.0f;

	bool isDay = true;

	const int GRASS_CAP = 30;
	const int timeInDay = 3334;
	int currentTime = 0;
	int grassBuyAmount = 1;
	int sheepCap = 5;
	int sheepBuyAmount = 1;
	int eatTimer = 1540; // Arbutary number, make sure maybe fix?
	int eatTimerCap = 1540;
	int wolvesAbout;

	int const maxUp_sheepAmount = 5;
	int const maxUp_woolSell = 5;
	int const maxUp_grassAmount = 5;
	int const maxUp_sheepCap = 5;

	std::vector<Sheep> sheepArray;
	std::vector<Grass> grassNodeArray;
	std::vector<Sheep*> herd;

	// For shearing
	struct WoolParticle
	{
		sf::CircleShape shape;
		sf::Vector2f velocity;
		float lifetime;
		bool canCollect = false;
		float collectDelay = 1.f;
	};

	std::vector<WoolParticle> woolParticles;


public:
	int WorldTime();
	sf::Color DaylightCycle();
	void Draw(sf::RenderWindow& window);
	void PassGrassToSheep();
	void Update(float, sf::Vector2i);
	void FixedUpdate(sf::Vector2i mousePos);
	World()
	{
		bg.setSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
		econ.setUpUpgradeMaps();
	}
	~World()
	{

	}
};


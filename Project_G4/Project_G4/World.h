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
	void woolCollectFunc(sf::Vector2i mousePos);

	void displayCosts(sf::Vector2i mousePos);

	float transition = 0.0f;
	float sheepHeartCooldown = 0.f;
	float sheepHeartCooldownCap = 0.5f;

	bool isDay = true;
	bool showHoverText = false;

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

	// To advoid new classes, Im making structs
	// 
	// For wool particles that pop out after shearing
	struct WoolParticle
	{
		sf::CircleShape shape;
		sf::Vector2f velocity;
		bool canCollect = false;
		float collectDelay = 1.f;
	};

	// For the HUD element telling the player how much theyve earned from wool
	struct FloatingText
	{
		// --- Collecting wool ---
		sf::Text text;
		sf::Vector2f velocity;
		float lifetime = 1.5f;
		float fadeSpeed = 170.f; // This will decerease the alpha value overtime, to look like its fading
	};

	std::vector<WoolParticle> woolParticles;
	std::vector<FloatingText> floatingTexts;

	sf::Font Font;
	sf::Text upgradeText;


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
		Font.loadFromFile("ASSETS/FONT/BebasNeue.otf");

		upgradeText.setFont(Font);
		upgradeText.setCharacterSize(18);
		upgradeText.setFillColor(sf::Color::White);
	}
	~World()
	{

	}
};


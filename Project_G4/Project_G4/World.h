#pragma once  
#include "Global.h"  
#include "Grass.h"  
#include "Fence.h"  
#include "Sheep.h"  
#include "Economy.h"  
#include "Funds_Enum.h"  
#include "Wolf.h"  
#include "Dog.h"  
#include "Combiner.h"

// Day -> (134, 172, 19)
// Night -> (40, 108, 89)

class World  
{  
private:  

  Grass grassNode;  
  Economy econ;  
  Sheep sheep;  
  Fence fence;  
  std::optional<Wolf> wolf;
  Dog dog;  
  Combiner combiner;

  sf::RectangleShape bg;
  sf::Sprite combinerSprite;
  sf::Texture combinerTexture;

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
  void woolCollectFunc(sf::Vector2i mousePos, int value);  

  void combineFunc(std::vector< Sheep>&);

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
  int wolvesAbout = 0; // Initialize wolvesAbout to resolve uninitialized variable warning yokey
  int closeTimer = 0;

  int const maxUp_sheepAmount = 5;  
  int const maxUp_woolSell = 5;  
  int const maxUp_grassAmount = 5;  
  int const maxUp_sheepCap = 5;  

  std::vector<Sheep> sheepArray;  
  std::vector<Grass> grassNodeArray;  
  std::vector<Sheep*> herd;  

  sf::RectangleShape getInnerFence() { return fence.getRectArea(); }

  sf::Vector2f wolfPos;

  // To avoid new classes, I'm making structs
  //  
  // For wool particles that pop out after shearing
  struct WoolParticle
  {  
      sf::CircleShape shape;
      sf::Vector2f velocity;  
      bool canCollect = false;  
      float collectDelay = 1.f; 
      Sheep* sourceSheep = nullptr;
  };  

  // For the HUD element telling the player how much they've earned from wool  
  struct FloatingText  
  {  
      // --- Collecting wool ---  
      sf::Text text;  
      sf::Vector2f velocity;  
      float lifetime = 1.5f;  
      float fadeSpeed = 170.f; // This will decrease the alpha value over time, to look like it's fading  
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
      wolvesAbout = 0; // Initialize wolvesAbout in the constructor  

	  combinerTexture.loadFromFile("ASSETS/ART/tempCombiner.png");
	  combinerSprite.setTexture(combinerTexture);
	  combinerSprite.setOrigin(combinerSprite.getGlobalBounds().width / 2, combinerSprite.getGlobalBounds().height / 2);
	  combinerSprite.setPosition(575.f, 850.f);
  }  
  ~World()  
  {  

  }  
};

#pragma once
#include "Global.h"
#include "Sheep.h" 
#include "WoolParticle.h"

class World; // Forward declaration, because I was getting an error

class Wolf
{
public:

	Wolf()
	{
	}
	Wolf(int spawnLocale);

	void Draw(sf::RenderWindow& window);
	void Hunt(std::vector<Sheep*>& flock, float deltaTime, sf::RectangleShape innerGrass, World* world);
	void spawnWolf(int spawnPos);
	void setStunned(float time) { stunTimer = time; }
	void clearTarget() { targetSheep = nullptr; isEating = false; } // Helper for bug with retargeting sheep

	bool isStunned() const { return stunTimer > 0.f; }
	bool isEatingSheep() const { return isEating; }
	bool isDead() const { return isWolfDead; };


	Sheep* getTarget() const { return targetSheep; }

	sf::Vector2f getPosition() { return wolfBody.getPosition(); };
	sf::FloatRect getBody() { return wolfBody.getGlobalBounds(); };


private:

	sf::CircleShape wolfBody;
	sf::CircleShape wolfHead;
	sf::ConvexShape wolfTail;
	sf::ConvexShape wolfEars;
	sf::ConvexShape wolfSnout;
	sf::Vector2f position;

	Sheep* targetSheep = nullptr;
	Sheep* FindClosestSheep(std::vector<Sheep*>& flock, sf::RectangleShape innerGrass);

	float stunTimer = 1.f;
	float eatTimer = 3.f;
	float eatDuration = 3.f;

	bool isEating = false;
	bool isWolfDead = false;
};


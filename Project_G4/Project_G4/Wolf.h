#pragma once
#include "Global.h"
#include "Sheep.h" 

class Wolf
{
public:
	Wolf()
	{
	}
	Wolf(int spawnLocale);
	void Draw(sf::RenderWindow& window);
	void Hunt(std::vector<Sheep*>& flock, float deltaTime);
	void spawnWolf(int spawnPos);

	sf::Vector2f getPosition() { return wolfBody.getPosition(); };
	sf::FloatRect getBody() { return wolfBody.getGlobalBounds(); };
private:
	sf::CircleShape wolfBody;
	sf::Vector2f position;
	Sheep* targetSheep = nullptr;

	Sheep* FindClosestSheep(std::vector<Sheep*>& flock);
};


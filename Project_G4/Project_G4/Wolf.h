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
	void setStunned(float time) { stunTimer = time; }

	bool isStunned() const { return stunTimer > 0.f; }

	sf::Vector2f getPosition() { return wolfBody.getPosition(); };
	sf::FloatRect getBody() { return wolfBody.getGlobalBounds(); };

private:

	sf::CircleShape wolfBody;
	sf::Vector2f position;

	Sheep* targetSheep = nullptr;
	Sheep* FindClosestSheep(std::vector<Sheep*>& flock);

	float stunTimer = 1.f;
};


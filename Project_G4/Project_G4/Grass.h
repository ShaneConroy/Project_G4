#pragma once
#include "Global.h"

class Grass
{
public:
	Grass()
	{
		grassNode.setFillColor(sf::Color(138, 225, 6));
		grassNode.setRadius(7);
        sf::Vector2f spawnPos = randomPosition({ SCREEN_WIDTH - 14, SCREEN_HEIGHT * 2/3 });
		grassNode.setPosition(spawnPos);
	}
	~Grass()
	{

	}
	sf::CircleShape grassNode;
private:
	sf::Vector2f randomPosition(const sf::Vector2f& vec)
	{
		std::random_device random;
		std::mt19937 randomInstance(random());
		std::uniform_real_distribution<float> distX(0.f, vec.x);
		std::uniform_real_distribution<float> distY(0.f, vec.y);

		float randomX = distX(randomInstance);
		float randomY = distY(randomInstance);

		std::cout << randomX << ", " << randomY<<"\n";
		return sf::Vector2f(randomX, randomY);
	}

};


#pragma once
#include "Global.h"
class Dog
{
public:
	Dog();

	void Update(sf::Vector2i mousePos);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() { return dogBody.getPosition(); }

private:

	void follow(sf::Vector2i mousePos);

	sf::CircleShape dogBody;
};


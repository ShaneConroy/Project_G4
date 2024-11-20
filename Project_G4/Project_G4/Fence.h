#include "Global.h"
#pragma once

class Fence
{
public:

	Fence()
	{
		fenceSquare.setFillColor(sf::Color(128, 71, 28));
		fenceSquare.setPosition(10, 534);
		sf::Vector2f size = { 1180.f, 260.f };
		fenceSquare.setSize(size);
		
		innerGrass.setFillColor(sf::Color(134, 172, 19));
		innerGrass.setPosition(20, 544);
		sf::Vector2f siez2 = { 1160.f, 240.f };
		innerGrass.setSize(siez2);

		exitGrass.setFillColor(sf::Color(134, 172, 19));
		sf::Vector2f size3 = { 200.f, 10.f };
		exitGrass.setPosition((fenceSquare.getSize().x / 2) - (size3.x/ 2), 534);
		exitGrass.setSize(size3);
	}
	~Fence()
	{
	}

	void UpdateGrass(sf::Color);
	void Draw(sf::RenderWindow& window);

private:

	sf::RectangleShape fenceSquare;
	sf::RectangleShape innerGrass;
	sf::RectangleShape exitGrass;

};


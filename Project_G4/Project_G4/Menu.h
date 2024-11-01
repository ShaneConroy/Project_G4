#pragma once
#include "Global.h"


class Menu
{
private:
	sf::RectangleShape menuBackGround;
	sf::Vector2f SCREEN_SIZE = { SCREEN_WIDTH, SCREEN_HEIGHT };
	sf::Sprite menuStartButton;
	sf::Texture menuStartTexture;

public:
	Menu()
	{
		menuBackGround.setFillColor(sf::Color(125, 125, 125));
		menuBackGround.setSize(SCREEN_SIZE);
		menuBackGround.setPosition(0, 0);

		menuStartTexture.loadFromFile("ASSETS/ART/startMenuTexture.png");
		menuStartButton.setTexture(menuStartTexture);
		menuStartButton.setPosition((SCREEN_SIZE.x / 2) - 50, (SCREEN_SIZE.y / 2) - 50);
	}

	~Menu()
	{

	}
	
	void Draw(sf::RenderWindow &window);
	bool StartButtonFunction(sf::Vector2i);


};


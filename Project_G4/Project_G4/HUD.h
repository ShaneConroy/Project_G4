#pragma once
#include "Global.h"

class HUD
{
public:

	HUD();

	void Draw(sf::RenderWindow& window);
	sf::Sprite getSellButton();
	sf::Sprite getBuyButton();

	void updateHUDMoney(int);

private:

	sf::Texture HUDTexture;
	sf::Sprite sellButton;
	sf::Sprite buyButton;
	sf::Sprite grassButton;

	sf::Texture numbersTexture;
	sf::Sprite num1;
	sf::Sprite num2;
	sf::Sprite num3;
	sf::Sprite num4;
	sf::Sprite num5;
	sf::Sprite num6;

	float timer = 0.0f;
	float timerCap = 6.0f;

	
};


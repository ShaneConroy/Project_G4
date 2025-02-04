#pragma once
#include "Global.h"

class HUD
{
public:

	HUD();

	void Draw(sf::RenderWindow& window);
	sf::Sprite getSellButton();
	sf::Sprite getBuyButton();

private:

	sf::Texture HUDTexture;
	sf::Sprite sellButton;
	sf::Sprite buyButton;

	float timer = 0.0f;
	float timerCap = 6.0f;

};


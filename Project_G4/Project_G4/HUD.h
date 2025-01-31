#pragma once
#include "Global.h"

class HUD
{
public:

	HUD();

	void Draw(sf::RenderWindow& window);
	void Update(sf::Vector2i mousePos);
	void setSellStatus(bool);
	bool getSellStatus();

	bool sellButtonClicked;

private:

	sf::Texture HUDTexture;
	sf::Sprite sellButton;
	
	float timer = 0.0f;
	float timerCap = 6.0f;

};


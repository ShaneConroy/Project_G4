#pragma once
#include "Global.h"
#include "World.h"
class HUD
{
public:

	HUD();

	void Draw(sf::RenderWindow& window);
	void Update(sf::Vector2i mousePos);
private:
	World world;

	sf::Texture HUDTexture;
	sf::Sprite sellButton;
	
	float timer = 0.0f;
	float timerCap = 5.0f;
};


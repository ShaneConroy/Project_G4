#pragma once
#include "Global.h"

class HUD
{
public:

	HUD();

	void Draw(sf::RenderWindow& window);
	sf::Sprite getSellButton();
	sf::Sprite getBuyButton();
	sf::Sprite getGrassButton();
	sf::Sprite getPopOutPanel();

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

	sf::Texture upgradeSpriteSheet;
	sf::Sprite sheepPurchaseAmountUpgrade;
	sf::Sprite sheepSellPriceUpgrade;
	sf::Sprite sheepMaxCapUpgrade;
	sf::Sprite grassPurchaseAmountUpgrade;

	sf::Texture popOutPanelTexture;
	sf::Sprite popOutPanel;

	bool poppedOut = false;

	float timer = 0.0f;
	float timerCap = 6.0f;

	
};


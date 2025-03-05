#pragma once
#include "Global.h"

class HUD
{
public:

	HUD();

	void Draw(sf::RenderWindow& window, bool);
	sf::Sprite& getSellButton() { return sellButton; };
	sf::Sprite& getBuyButton() { return buyButton; };
	sf::Sprite& getGrassButton() { return grassButton; };
	sf::Sprite& getPopOutPanel() { return popOutPanel; };

	void updateHUDMoney(int);

private:

	sf::Texture sellSheepTexture;
	sf::Sprite sellButton;

	sf::Texture buySheepTexture;
	sf::Sprite buyButton;

	sf::Texture buyGrassTexture;
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


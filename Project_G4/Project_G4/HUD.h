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
	sf::Sprite& getUpgradeButton_SheepAmount() { return sheepPurchaseAmountUpgrade; };
	sf::Sprite& getUpgradeButton_WoolSell() { return woolSellPriceUpgrade; };
	sf::Sprite& getUpgradeButton_MaxSheep() { return sheepMaxCapUpgrade; };
	sf::Sprite& getUpgradeButton_BetterGrass() { return grassPurchaseAmountUpgrade; };
	sf::Sprite& getStuckButton() { return stuckButton; };
	sf::Sprite& getWhistleButton() { return whistleButton; };
	sf::Sprite& getBuilding_Barn() { return barn; };
	sf::Sprite& getBuilding_Loom() { return loom; };
	sf::Sprite& getBuilding_Market() { return market; };
	sf::Sprite& getBuilding_Garden() { return garden; };
	sf::Sprite& getShearButton() { return shearButton; };
	sf::Sprite& getShears() { return shears; };
	sf::Sprite& getCombineButton() { return combineButton; };

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
	sf::Sprite woolSellPriceUpgrade;
	sf::Sprite sheepMaxCapUpgrade;
	sf::Sprite grassPurchaseAmountUpgrade;

	sf::Texture barnSpriteSheet;
	sf::Sprite barn;

	sf::Texture loomSpriteSheet;
	sf::Sprite loom;

	sf::Texture marketSpriteSheet;
	sf::Sprite market;

	sf::Texture gardenSpriteSheet;
	sf::Sprite garden;

	sf::Texture popOutPanelTexture;
	sf::Sprite popOutPanel;

	sf::Texture stuckButtonTexture;
	sf::Sprite stuckButton;

	sf::Texture whistleButtonTexture;
	sf::Sprite whistleButton;

	sf::Texture shearButtonTexture;
	sf::Sprite shearButton;

	sf::Texture shearsTexture;
	sf::Sprite shears;

	sf::Texture combineButtonTexture;
	sf::Sprite combineButton;

	bool poppedOut = false;

	float timer = 0.0f;
	float timerCap = 6.0f;

	float scal = 1.8;
};


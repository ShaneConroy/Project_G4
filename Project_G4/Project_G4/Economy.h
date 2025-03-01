#pragma once
#include "Global.h"
#include "Funds_Enum.h"
#include "Sheep.h"
#include "HUD.h"


class Economy
{
public:

	bool sheepPurchased = false;
	bool sheepSold = false;
	bool fertiliserPurchased = false;
	bool popOpen = false;

	void update();
	void addFunds(Funds_Enum fundType);
	void calculatePassiveIncome(int);

	void sellSheep(sf::Vector2i);
	void buySheep(sf::Vector2i);
	void buyGrass(sf::Vector2i);
	void popOutPanelFunc(sf::Vector2i);

	void draw(sf::RenderWindow&, bool);

	HUD hud;

private:

	Funds_Enum fundType;
	Sheep sheep;

	int currentFunds = 1000;

	int fertiliserPrice = 50;
	int sheepBuyPrice = 100;
	int sheepSellPrice = 50;

	int buySheepDelay;
	int buyDelayCap = 6;

	int sellDelay;
	int sellDelayCap = 6;

	int passiveIncome;
	int passiveIncomeTimer;
	int passiveIncomeTimerCap = 60;

	int buyGrassDelay;
	int buyGrassDelayCap = 6;

	int sellTimer;
	int sellTimerCap = 12;

	int buyTimer;
	int buyTimerCap = 12;

	int grassTimer;
	int grassTimerCap = 12;

	int popTimer;
	int popTimerCap = 12;

	void purchaseSheep();
	void purchaseGrass();

	int checkFunds();

};


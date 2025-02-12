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

	void update();
	void addFunds(Funds_Enum fundType);
	void calculatePassiveIncome(int);  
	void sellSheep(sf::Vector2i);
	void buySheep(sf::Vector2i);
	void draw(sf::RenderWindow&);

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
	int sellTimerCap = 1200;

	int buyTimer;
	int buyTimerCap = 1200;

	void purchaseFertiliser();
	void purchaseSheep();
	int checkFunds();

};


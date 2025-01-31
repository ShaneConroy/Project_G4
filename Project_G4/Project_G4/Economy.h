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

	void purchaseFertiliser();
	int checkFunds();
	void purchaseSheep();
	void sellSheep();

};


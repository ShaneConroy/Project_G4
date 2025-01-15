#pragma once
#include "Global.h"

class Economy
{
public:

	bool sheepPurchased = false;
	bool sheepSold = false;

	void update();
	void addFunds();

private:

	int currentFunds = 1000;
	int sheepBuyPrice = 100;
	int sheepSellPrice = 50;
	int buyDelay;
	int buyDelayCap = 6;
	int sellDelay;
	int sellDelayCap = 6;

	int checkFunds();
	void purchaseSheep();
	void sellSheep();
};


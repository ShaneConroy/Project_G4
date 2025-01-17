#include "Economy.h"

// Returns the players current funds
int Economy::checkFunds()
{
	return currentFunds;
}

// Adds money based on enum type
void Economy::addFunds(Funds_Enum fundType)
{
	if (fundType == Funds_Enum::sheepSold)
	{
		currentFunds += sheepSellPrice;
	}
	else if (fundType == Funds_Enum::passiveIncome)
	{
		currentFunds += passiveIncome;
	}
}

// Calculate passive income
void Economy::calculatePassiveIncome(int sheepAmount)
{
	passiveIncome = sheepAmount * 10;
}

// Handles buying sheep
void Economy::purchaseSheep()
{
	if (checkFunds() >= sheepBuyPrice)
	{
		if (buySheepDelay > 0)
		{
			buySheepDelay--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			if (buySheepDelay <= 0)
			{
				sheepPurchased = true;
				buySheepDelay = buyDelayCap;
				currentFunds -= sheepBuyPrice;
			}
		}
	}
}

// Sells sheep
void Economy::sellSheep()
{
	if (sellDelay > 0)
	{
		sellDelay--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		if (sellDelay <= 0)
		{
			sheepSold = true;
			sellDelay = sellDelayCap;
		}
	}

}

void Economy::purchaseFertiliser()
{
	if (checkFunds() >= fertiliserPrice)
	{
		if (buyGrassDelay > 0)
		{
			buyGrassDelay--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			if (buyGrassDelay <= 0)
			{
				fertiliserPurchased = true;
				currentFunds -= fertiliserPrice;
				buyGrassDelay = buyGrassDelayCap;
			}
		}
	}
}

void Economy::update()
{
	purchaseSheep();
	sellSheep();
	purchaseFertiliser();
	// Every 60 frames, add passive income
	if (passiveIncomeTimer > 0)
		passiveIncomeTimer--;
	if (passiveIncomeTimer <= 0)
	{
		addFunds(Funds_Enum::passiveIncome);
		passiveIncomeTimer = passiveIncomeTimerCap;
	}
	//std::cout << checkFunds() << "\n";
}

#include "Economy.h"

// Returns the players current funds
int Economy::checkFunds()
{
	return currentFunds;
}

void Economy::addFunds()
{
	currentFunds += sheepSellPrice;
}

void Economy::purchaseSheep()
{
	if (checkFunds() >= sheepBuyPrice)
	{
		if (buyDelay > 0)
		{
			buyDelay--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			if (buyDelay <= 0)
			{
				sheepPurchased = true;
				buyDelay = buyDelayCap;
				currentFunds -= sheepBuyPrice;
			}
		}
	}
}

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

void Economy::update()
{
	purchaseSheep();
	sellSheep();
	std::cout << checkFunds() << "\n";
}

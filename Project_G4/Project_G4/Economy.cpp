#include "Economy.h"

// Returns the players current funds
int Economy::checkFunds()
{
	return currentFunds;
}

void Economy::purchaseSheep()
{
	if (checkFunds() > sheepBuyPrice)
	{
		// Add sheep
	}
}

void Economy::sellSheep()
{
	// Add sheepSellPrice to currentFunds
}

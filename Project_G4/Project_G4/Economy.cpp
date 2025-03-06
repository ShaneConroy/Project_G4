#include "Economy.h"

// Returns the players current funds
int Economy::checkFunds()
{
	return currentFunds;
}

// Adds money based on enum type
void Economy::addFunds(Funds_Enum fundType)
{
	int amountToAdd = 0;

	if (fundType == Funds_Enum::sheepSold)
	{
		amountToAdd = sheepSellPrice;
	}
	else if (fundType == Funds_Enum::passiveIncome)
	{
		amountToAdd = passiveIncome;
	}

	// Prevent exceeding max funds limit 
	if (currentFunds + amountToAdd > 999999)
	{
		currentFunds = 999999;
	}
	else
	{
		currentFunds += amountToAdd;
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
		sheepPurchased = true;
		buySheepDelay = buyDelayCap;
		currentFunds -= sheepBuyPrice;
	}
}

void Economy::purchaseGrass()
{
	if (checkFunds() >= fertiliserPrice)
	{
		fertiliserPurchased = true;
		buyGrassDelay = buyGrassDelayCap;
		currentFunds -= fertiliserPrice;
	}
}

// Sells sheep
void Economy::sellSheep(sf::Vector2i mousePos)
{
	if (sellTimer > 0.0f)
	{
		sellTimer -= 1.0f;

		// Greys out for a sec for visual feedback
		sf::Color color = hud.getSellButton().getColor();
		color.a = 128;
		hud.getSellButton().setColor(color);
	}
	else if (sellTimer <= 0.0f)
	{
		sf::Color color = hud.getSellButton().getColor();
		color.a = 255;
		hud.getSellButton().setColor(color);

		if (popOpen)
		{
			if (mousePos.x >= hud.getSellButton().getPosition().x &&
				mousePos.x <= hud.getSellButton().getPosition().x + hud.getSellButton().getGlobalBounds().width &&
				mousePos.y >= hud.getSellButton().getPosition().y &&
				mousePos.y <= hud.getSellButton().getPosition().y + hud.getSellButton().getGlobalBounds().height)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sheepSold = true;
					sellTimer = sellTimerCap;
				}
			}
		}
	}
}

void Economy::buySheep(sf::Vector2i mousePos)
{
    if (buyTimer > 0.0f)
    {
        buyTimer -= 1.0f;

		sf::Color color = hud.getBuyButton().getColor();
		color.a = 128;
		hud.getBuyButton().setColor(color);
    }
    else if (buyTimer <= 0.0f)
    {
		sf::Color color = hud.getBuyButton().getColor();
		color.a = 255;
		hud.getBuyButton().setColor(color);

		if (popOpen)
		{
			if (mousePos.x >= hud.getBuyButton().getPosition().x &&
				mousePos.x <= hud.getBuyButton().getPosition().x + hud.getBuyButton().getGlobalBounds().width &&
				mousePos.y >= hud.getBuyButton().getPosition().y &&
				mousePos.y <= hud.getBuyButton().getPosition().y + hud.getBuyButton().getGlobalBounds().height)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					purchaseSheep();
					buyTimer = buyTimerCap;
				}
			}
		}
    }
}


void Economy::buyGrass(sf::Vector2i mousePos)
{
	if (grassTimer > 0.0f)
	{
		grassTimer -= 1.0f;

		sf::Color color = hud.getGrassButton().getColor();
		color.a = 128;
		hud.getGrassButton().setColor(color);
	}
	else if (grassTimer <= 0.0f)
    {
		sf::Color color = hud.getGrassButton().getColor();
		color.a = 255;
		hud.getGrassButton().setColor(color);

		if (popOpen)
		{
			if (mousePos.x >= hud.getGrassButton().getPosition().x &&
				mousePos.x <= hud.getGrassButton().getPosition().x + hud.getGrassButton().getGlobalBounds().width &&
				mousePos.y >= hud.getGrassButton().getPosition().y &&
				mousePos.y <= hud.getGrassButton().getPosition().y + hud.getGrassButton().getGlobalBounds().height)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					purchaseGrass();
					grassTimer = grassTimerCap;
				}
			}
		}
    }
}

void Economy::popOutPanelFunc(sf::Vector2i mousePos)
{
	if (popTimer > 0.0f)
	{
		popTimer -= 1.0f;
	}
	else if (popTimer <= 0.0f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		{
			popOpen = !popOpen;
			popTimer = popTimerCap;
		}
	}

	if (popOpen)
	{
		hud.getPopOutPanel().setPosition(-120, 10);
	}
	else if (!popOpen)
	{
		hud.getPopOutPanel().setPosition(-410, 10);
	}
}

void Economy::draw(sf::RenderWindow& window, bool popOut)
{
	hud.Draw(window, popOut);
}

void Economy::update()
{
	// Every 60 frames, add passive income
	if (passiveIncomeTimer > 0)
		passiveIncomeTimer--;
	if (passiveIncomeTimer <= 0)
	{
		addFunds(Funds_Enum::passiveIncome);
		passiveIncomeTimer = passiveIncomeTimerCap;
	}
	hud.updateHUDMoney(currentFunds);
}

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
	else if (fundType == Funds_Enum::refund)
	{
		amountToAdd = sheepBuyPrice;
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
		buySheepDelay = buttonDelay;
		currentFunds -= sheepBuyPrice;
	}
}

void Economy::purchaseGrass()
{
	if (checkFunds() >= fertiliserPrice)
	{
		fertiliserPurchased = true;
		buyGrassDelay = buttonDelay;
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
					sellTimer = buttonDelay;
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

		sf::Color color = hud.getBuyButton().getColor(); // When you cant press button, grey
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
					buyTimer = buttonDelay;
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
					grassTimer = buttonDelay;
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
			popTimer = buttonDelay;
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

// TODO // Have prices attached to the upgrades. Grey out if you cant buy 
void Economy::upgradeMaxSheep(sf::Vector2i mousePos)
{
	if (up_MaxSheepTimer > 0.0f)
	{
		up_MaxSheepTimer -= 1.0f;

		sf::Color color = hud.getUpgradeButton_MaxSheep().getColor();
		color.a = 128;
		hud.getUpgradeButton_MaxSheep().setColor(color);
	}
	else if (up_MaxSheepTimer <= 0.0f)
	{
		sf::Color color = hud.getUpgradeButton_MaxSheep().getColor();
		color.a = 255;
		hud.getUpgradeButton_MaxSheep().setColor(color);

		if (popOpen)
		{
			if (mousePos.x >= hud.getUpgradeButton_MaxSheep().getPosition().x &&
				mousePos.x <= hud.getUpgradeButton_MaxSheep().getPosition().x + hud.getUpgradeButton_MaxSheep().getGlobalBounds().width &&
				mousePos.y >= hud.getUpgradeButton_MaxSheep().getPosition().y &&
				mousePos.y <= hud.getUpgradeButton_MaxSheep().getPosition().y + hud.getUpgradeButton_MaxSheep().getGlobalBounds().height)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					auto& sheepUpgrade = upgradeMap["up_MaxSheep"]; // Get the key
					float upgradePrice = sheepUpgrade.begin()->first; // Look at the first yoke in map

					// Check if player can afford upgrade
					if (currentFunds >= upgradePrice)
					{
						applyUpgrade(upgradeMap["up_MaxSheep"]);
						up_MaxSheepBool = true;
						barnLevel += 1;
					}

					up_MaxSheepTimer = buttonDelay;
				}
			}
		}
	}
}

void Economy::upgradeWoolPrice(sf::Vector2i mousePos)
{
	if (up_WoolPriceTimer > 0.0f)
	{
		up_WoolPriceTimer -= 1.0f;

		sf::Color color = hud.getUpgradeButton_WoolSell().getColor();
		color.a = 128;
		hud.getUpgradeButton_WoolSell().setColor(color);
	}
	else if (up_WoolPriceTimer <= 0.0f)
	{
		sf::Color color = hud.getUpgradeButton_WoolSell().getColor();
		color.a = 255;
		hud.getUpgradeButton_WoolSell().setColor(color);

		if (popOpen)
		{
			if (mousePos.x >= hud.getUpgradeButton_WoolSell().getPosition().x &&
				mousePos.x <= hud.getUpgradeButton_WoolSell().getPosition().x + hud.getUpgradeButton_WoolSell().getGlobalBounds().width &&
				mousePos.y >= hud.getUpgradeButton_WoolSell().getPosition().y &&
				mousePos.y <= hud.getUpgradeButton_WoolSell().getPosition().y + hud.getUpgradeButton_WoolSell().getGlobalBounds().height)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					auto& sheepUpgrade = upgradeMap["up_WoolSell"]; // Get the key
					float upgradePrice = sheepUpgrade.begin()->first; // Look at the first yoke in map

					// Check if player can afford upgrade
					if (currentFunds >= upgradePrice)
					{
						applyUpgrade(upgradeMap["up_WoolSell"]);
						up_WoolSellPrice = true;
						loomLevel += 1;
					}

					up_WoolPriceTimer = buttonDelay;
				}
			}
		}
	}
}

void Economy::upgradeSheepPurchaseAmount(sf::Vector2i mousePos)
{
	if (up_SheepBuyAmountTimer > 0.0f)
	{
		up_SheepBuyAmountTimer -= 1.0f;

		sf::Color color = hud.getUpgradeButton_SheepAmount().getColor();
		color.a = 128;
		hud.getUpgradeButton_SheepAmount().setColor(color);
	}
	else if (up_SheepBuyAmountTimer <= 0.0f)
	{
		sf::Color color = hud.getUpgradeButton_SheepAmount().getColor();
		color.a = 255;
		hud.getUpgradeButton_SheepAmount().setColor(color);

		if (popOpen)
		{
			if (mousePos.x >= hud.getUpgradeButton_SheepAmount().getPosition().x &&
				mousePos.x <= hud.getUpgradeButton_SheepAmount().getPosition().x + hud.getUpgradeButton_SheepAmount().getGlobalBounds().width &&
				mousePos.y >= hud.getUpgradeButton_SheepAmount().getPosition().y &&
				mousePos.y <= hud.getUpgradeButton_SheepAmount().getPosition().y + hud.getUpgradeButton_SheepAmount().getGlobalBounds().height)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					auto& sheepUpgrade = upgradeMap["up_MoreSheep"]; // Get the key
					float upgradePrice = sheepUpgrade.begin()->first; // Look at the first yoke in map

					// Check if player can afford upgrade
					if (currentFunds >= upgradePrice)
					{
						applyUpgrade(upgradeMap["up_MoreSheep"]);
						up_SheepAmountBool = true;
						marketLevel += 1;
					}

					up_SheepBuyAmountTimer = buttonDelay;
				}
			}
		}
	}
}

void Economy::upgradeGrassPurchaseAmount(sf::Vector2i mousePos)
{
	if (up_GrassBuyAmountTimer > 0.0f)
	{
		up_GrassBuyAmountTimer -= 1.0f;

		sf::Color color = hud.getUpgradeButton_BetterGrass().getColor();
		color.a = 128;
		hud.getUpgradeButton_BetterGrass().setColor(color);
	}
	else if (up_GrassBuyAmountTimer <= 0.0f)
	{
		sf::Color color = hud.getUpgradeButton_BetterGrass().getColor();
		color.a = 255;
		hud.getUpgradeButton_BetterGrass().setColor(color);

		if (popOpen)
		{
			if (mousePos.x >= hud.getUpgradeButton_BetterGrass().getPosition().x &&
				mousePos.x <= hud.getUpgradeButton_BetterGrass().getPosition().x + hud.getUpgradeButton_BetterGrass().getGlobalBounds().width &&
				mousePos.y >= hud.getUpgradeButton_BetterGrass().getPosition().y &&
				mousePos.y <= hud.getUpgradeButton_BetterGrass().getPosition().y + hud.getUpgradeButton_BetterGrass().getGlobalBounds().height)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					auto& sheepUpgrade = upgradeMap["up_MoreGrass"]; // Get the key
					float upgradePrice = sheepUpgrade.begin()->first; // Look at the first yoke in map

					// Check if player can afford upgrade
					if (currentFunds >= upgradePrice)
					{
						applyUpgrade(upgradeMap["up_MoreGrass"]);
						up_GrassAmountBool = true;
						gardenLevel += 1;
					}

					up_GrassBuyAmountTimer = buttonDelay;
				}
			}
		}
	}
}

void Economy::stuckButtonFunc(sf::Vector2i mousePos)
{
	if (stuckTimer > 0.0f)
	{
		stuckTimer -= 1.0f;

		sf::Color color = hud.getStuckButton().getColor();
		color.a = 128;
		hud.getStuckButton().setColor(color);
	}
	else if (stuckTimer <= 0.0f)
	{
		sf::Color color = hud.getGrassButton().getColor();
		color.a = 255;
		hud.getStuckButton().setColor(color);

		if (popOpen)
		{
			if (mousePos.x >= hud.getStuckButton().getPosition().x &&
				mousePos.x <= hud.getStuckButton().getPosition().x + hud.getStuckButton().getGlobalBounds().width &&
				mousePos.y >= hud.getStuckButton().getPosition().y &&
				mousePos.y <= hud.getStuckButton().getPosition().y + hud.getStuckButton().getGlobalBounds().height)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					stuck = true;
					stuckTimer = buttonDelay;
				}
			}
		}
	}
}

void Economy::whistleButtonFunc(sf::Vector2i mousePos)
{
	if (whistleTimer > 0.0f)
	{
		whistleTimer -= 1.0f;

		sf::Color color = hud.getWhistleButton().getColor();
		color.a = 128;
		hud.getWhistleButton().setColor(color);
	}
	else if (whistleTimer <= 0.0f)
	{
		sf::Color color = hud.getWhistleButton().getColor();
		color.a = 255;
		hud.getWhistleButton().setColor(color);

		if (mousePos.x >= hud.getWhistleButton().getPosition().x &&
			mousePos.x <= hud.getWhistleButton().getPosition().x + hud.getWhistleButton().getGlobalBounds().width &&
			mousePos.y >= hud.getWhistleButton().getPosition().y &&
			mousePos.y <= hud.getWhistleButton().getPosition().y + hud.getWhistleButton().getGlobalBounds().height)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				whistle = true;
				whistleTimer = buttonDelay;
			}
		}
	}
}

void Economy::upgradeBarn(sf::IntRect newTexture)
{
	hud.getBuilding_Barn().setTextureRect(newTexture);
}

// Makes a map which links a string to a float,float, shuold make upgrades easier
void Economy::setUpUpgradeMaps()
{
	std::vector<std::string> upgradeKeys = { "up_MaxSheep", "up_WoolSell", "up_MoreSheep", "up_MoreGrass"};

	std::vector<std::pair<float, float>> upgradeStats = { { 2500, 1.25 }, { 5000, 2.5 }, { 12000, 1.60 }, { 8000, 1.20 } };

	if (upgradeKeys.size() == upgradeStats.size())
	{
		for (size_t i = 0; i < upgradeKeys.size(); i++)
		{
			upgradeMap[upgradeKeys[i]] = { upgradeStats[i] }; // Mapping
		}
	}
}

void Economy::applyUpgrade(std::map<float, float>& stats)
{
	auto iter = stats.begin();
	if (iter != stats.end())
	{
		float basePrice = iter->first; // Price
		float costScalar = iter->second; // Scalar

		// Check if the player can afford the upgrade
		if (currentFunds >= basePrice)
		{
			currentFunds -= basePrice;

			float newPrice = basePrice * costScalar;

			stats.erase(iter); // Remove the old price and put new one in
			stats[newPrice] = costScalar;
		}
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

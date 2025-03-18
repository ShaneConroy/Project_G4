#include "HUD.h"

HUD::HUD()
{
	sellSheepTexture.loadFromFile("Assets/ART/sellIcon.png");
	sellButton.setTexture(sellSheepTexture);
	sellButton.setPosition(105, 25);
	sellButton.setScale(scal, scal);

	buySheepTexture.loadFromFile("Assets/ART/sheepBuyIcon.png");
	buyButton.setTexture(buySheepTexture);
	buyButton.setPosition(10, 25);
	buyButton.setScale(scal, scal);

	buyGrassTexture.loadFromFile("Assets/ART/buyGrassIcon.png");
	grassButton.setTexture(buyGrassTexture);
	grassButton.setPosition(10, 120);
	grassButton.setScale(scal, scal);

	numbersTexture.loadFromFile("Assets/ART/numbers.png");
	num1.setTexture(numbersTexture);
	num2.setTexture(numbersTexture);
	num3.setTexture(numbersTexture);
	num4.setTexture(numbersTexture);
	num5.setTexture(numbersTexture);
	num6.setTexture(numbersTexture);
	num1.setTextureRect(sf::IntRect(227, 168, 58, 59));
	num2.setTextureRect(sf::IntRect(227, 168, 58, 59));
	num3.setTextureRect(sf::IntRect(227, 168, 58, 59));
	num4.setTextureRect(sf::IntRect(227, 168, 58, 59));
	num5.setTextureRect(sf::IntRect(227, 168, 58, 59));
	num6.setTextureRect(sf::IntRect(227, 168, 58, 59));

	num1.setPosition(1125, 10);
	num2.setPosition(1067, 10);
	num3.setPosition(1009, 10);
	num4.setPosition(951, 10);
	num5.setPosition(893, 10);
	num6.setPosition(835, 10);

	upgradeSpriteSheet.loadFromFile("Assets/ART/upgradeSpritesheet.png");
	sheepPurchaseAmountUpgrade.setTexture(upgradeSpriteSheet);
	woolSellPriceUpgrade.setTexture(upgradeSpriteSheet);
	sheepMaxCapUpgrade.setTexture(upgradeSpriteSheet);
	grassPurchaseAmountUpgrade.setTexture(upgradeSpriteSheet);
	sheepPurchaseAmountUpgrade.setTextureRect(sf::IntRect(0, 0, 50, 50));
	woolSellPriceUpgrade.setTextureRect(sf::IntRect(55, 0, 50, 50));
	sheepMaxCapUpgrade.setTextureRect(sf::IntRect(110, 0, 50, 50));
	grassPurchaseAmountUpgrade.setTextureRect(sf::IntRect(165, 0, 50, 50));

	sheepPurchaseAmountUpgrade.setPosition(10, 250);
	woolSellPriceUpgrade.setPosition(105, 250);
	sheepMaxCapUpgrade.setPosition(10, 345);
	grassPurchaseAmountUpgrade.setPosition(105, 345);

	sheepPurchaseAmountUpgrade.setScale(scal, scal);
	woolSellPriceUpgrade.setScale(scal, scal);
	sheepMaxCapUpgrade.setScale(scal, scal);
	grassPurchaseAmountUpgrade.setScale(scal, scal);

	popOutPanelTexture.loadFromFile("Assets/ART/popOutPanel.png");
	popOutPanel.setTexture(popOutPanelTexture);
	popOutPanel.setPosition(0, 0);
	popOutPanel.setScale(0.95, 0.95);

	barnSpriteSheet.loadFromFile("Assets/ART/barnSpriteSheet.png");
	barn.setTexture(barnSpriteSheet);
	barn.setTextureRect(sf::IntRect(5, 0, 379, 128));
	barn.setPosition(100, 0);
	barn.setScale(0.5, 0.5);

	stuckButtonTexture.loadFromFile("Assets/ART/stuckIcon.png");
	stuckButton.setTexture(stuckButtonTexture);
	stuckButton.setPosition(10, 495);
	stuckButton.setScale(0.45, 0.45);

	whistleButtonTexture.loadFromFile("Assets/ART/whistleIcon.png");
	whistleButton.setTexture(whistleButtonTexture);
	whistleButton.setPosition(1130, 75);
	whistleButton.setScale(0.95, 0.95);
}

void HUD::Draw(sf::RenderWindow& window, bool popOut)
{
	window.draw(barn);

	window.draw(popOutPanel);

	window.draw(num1);
	window.draw(num2);
	window.draw(num3);
	window.draw(num4);
	window.draw(num5);
	window.draw(num6);

	window.draw(whistleButton);

	// Only draw if popOut is open
	if (popOut)
	{
		window.draw(sellButton);
		window.draw(buyButton);
		window.draw(grassButton);

		window.draw(sheepPurchaseAmountUpgrade);
		window.draw(woolSellPriceUpgrade);
		window.draw(sheepMaxCapUpgrade);
		window.draw(grassPurchaseAmountUpgrade);

		window.draw(stuckButton);
	}

}

// Called by Economy, check how much mullah we got
void HUD::updateHUDMoney(int currentFunds)
{

	// Convert to string
	std::string funds = std::to_string(currentFunds);
	int length = funds.length();

	// Default to blank
	sf::IntRect blankRect(161, 168, 59, 59);
	num1.setTextureRect(blankRect);
	num2.setTextureRect(blankRect);
	num3.setTextureRect(blankRect);
	num4.setTextureRect(blankRect);
	num5.setTextureRect(blankRect);
	num6.setTextureRect(blankRect);

	// Digit mappings
	std::map<char, sf::IntRect> digitRects = {
		{'0', sf::IntRect(94, 169, 58, 58)},
		{'1', sf::IntRect(26, 33, 58, 58)},
		{'2', sf::IntRect(94, 33, 58, 58)},
		{'3', sf::IntRect(161, 33, 58, 58)},
		{'4', sf::IntRect(227, 33, 58, 58)},
		{'5', sf::IntRect(27, 101, 58, 58)},
		{'6', sf::IntRect(95, 101, 58, 58)},
		{'7', sf::IntRect(161, 101, 58, 58)},
		{'8', sf::IntRect(227, 101, 58, 58)},
		{'9', sf::IntRect(27, 169, 58, 58)}
	};

	// Sprites from right to left
	sf::Sprite* digits[] = { &num6, &num5, &num4, &num3, &num2, &num1 };

	for (int i = 0; i < length; ++i)
	{
		char digit = funds[i];
		sf::IntRect rect = digitRects[digit];

		digits[6 - length + i]->setTextureRect(rect);
	}
}


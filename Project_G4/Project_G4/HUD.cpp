#include "HUD.h"

HUD::HUD()
{
	HUDTexture.loadFromFile("Assets/ART/icons.png");
	sellButton.setTexture(HUDTexture);
	sellButton.setTextureRect(sf::IntRect(263, 264, 73, 77));
	sellButton.setPosition(0, 0);
	sellButton.setScale(0.5f, 0.5f);

	buyButton.setTexture(HUDTexture);
	buyButton.setTextureRect(sf::IntRect(104, 100, 72, 77));
	buyButton.setPosition(0, 50);
	buyButton.setScale(0.5, 0.5);

	grassButton.setTexture(HUDTexture);
	grassButton.setTextureRect(sf::IntRect(104, 100, 72, 77));
	grassButton.setPosition(50, 50);
	grassButton.setScale(0.5, 0.5);

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
	sheepSellPriceUpgrade.setTexture(upgradeSpriteSheet);
	sheepMaxCapUpgrade.setTexture(upgradeSpriteSheet);
	grassPurchaseAmountUpgrade.setTexture(upgradeSpriteSheet);
	sheepPurchaseAmountUpgrade.setTextureRect(sf::IntRect(8, 13, 214, 192));
	sheepSellPriceUpgrade.setTextureRect(sf::IntRect(267, 17, 250, 190));
	sheepMaxCapUpgrade.setTextureRect(sf::IntRect(533, 15, 250, 190));
	grassPurchaseAmountUpgrade.setTextureRect(sf::IntRect(794, 5, 229, 206));

	sheepPurchaseAmountUpgrade.setPosition(0, 100);
	sheepSellPriceUpgrade.setPosition(0, 200);
	sheepMaxCapUpgrade.setPosition(0, 300);
	grassPurchaseAmountUpgrade.setPosition(0, 400);

	sheepPurchaseAmountUpgrade.setScale(0.5, 0.5);
	sheepSellPriceUpgrade.setScale(0.5, 0.5);
	sheepMaxCapUpgrade.setScale(0.5, 0.5);
	grassPurchaseAmountUpgrade.setScale(0.5, 0.5);

	popOutPanelTexture.loadFromFile("Assets/ART/popOutPanel.png");
	popOutPanel.setTexture(popOutPanelTexture);
	popOutPanel.setPosition(0, 0);
	popOutPanel.setScale(0.75, 0.75);
}

void HUD::Draw(sf::RenderWindow& window, bool popOut)
{
	window.draw(popOutPanel);

	window.draw(num1);
	window.draw(num2);
	window.draw(num3);
	window.draw(num4);
	window.draw(num5);
	window.draw(num6);

	// Only draw if popOut is open
	if (popOut)
	{
		window.draw(sellButton);
		window.draw(buyButton);
		window.draw(grassButton);

		window.draw(sheepPurchaseAmountUpgrade);
		window.draw(sheepSellPriceUpgrade);
		window.draw(sheepMaxCapUpgrade);
		window.draw(grassPurchaseAmountUpgrade);
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


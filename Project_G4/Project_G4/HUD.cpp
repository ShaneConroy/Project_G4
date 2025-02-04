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
}

void HUD::Draw(sf::RenderWindow& window)
{
	window.draw(sellButton);
	window.draw(buyButton);
}

sf::Sprite HUD::getSellButton()
{
	return sellButton;
}

sf::Sprite HUD::getBuyButton()
{
	return buyButton;
}

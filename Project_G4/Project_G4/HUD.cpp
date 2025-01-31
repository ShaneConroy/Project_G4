#include "HUD.h"

HUD::HUD()
{
	HUDTexture.loadFromFile("Assets/ART/icons.png");
	sellButton.setTexture(HUDTexture);
	sellButton.setTextureRect(sf::IntRect(263, 264, 73, 77));
	sellButton.setPosition(0, 0);
	sellButton.setScale(0.5f, 0.5f);
}

void HUD::Draw(sf::RenderWindow& window)
{
	window.draw(sellButton);
}

void HUD::Update(sf::Vector2i mousePos)
{
	if (timer > 0.0f)
	{
		timer -= 1.0f;
	}
	else if(timer <= 0.0f)
	{
		if (mousePos.x >= sellButton.getPosition().x &&
			mousePos.x <= sellButton.getPosition().x + sellButton.getGlobalBounds().width &&
			mousePos.y >= sellButton.getPosition().y &&
			mousePos.y <= sellButton.getPosition().y + sellButton.getGlobalBounds().height)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				setSellStatus(true);
				std::cout << "sellButtonClicked" << "\n";
				timer = timerCap;
			}
		}
	}
}

bool HUD::getSellStatus()
{
	return sellButtonClicked;
}

void HUD::setSellStatus(bool booli)
{
	sellButtonClicked = booli;
}

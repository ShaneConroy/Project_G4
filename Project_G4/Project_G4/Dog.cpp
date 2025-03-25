#include "Dog.h"

Dog::Dog()
{
	dogBody.setRadius(20.f);
	dogBody.setOrigin(dogBody.getPosition().x + dogBody.getRadius(), dogBody.getPosition().y + dogBody.getRadius());
	dogBody.setFillColor(sf::Color(165, 42, 42));
	dogBody.setPosition(300, 300);
}

void Dog::Update(sf::Vector2i mousePos)
{
	follow(mousePos);
}

void Dog::follow(sf::Vector2i mousePos)
{

	if (mousePos.x < SCREEN_WIDTH && mousePos.x > 0 && mousePos.y < SCREEN_HEIGHT && mousePos.y > 0)
	{
		sf::Vector2f currentPos = dogBody.getPosition();
		sf::Vector2f targetPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

		float speed = 0.01f;
		dogBody.setPosition(currentPos + speed * (targetPos - currentPos));
	}
	else {
		dogBody.setPosition(dogBody.getPosition());
	}
}

void Dog::Draw(sf::RenderWindow& window)
{
	window.draw(dogBody);
}
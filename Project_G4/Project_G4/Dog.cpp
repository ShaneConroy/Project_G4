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

// Create Bark
void Dog::Bark()
{
    if (barkCooldown <= 0.f)
    {
        barkTriggered = true;
        barkCooldown = barkCooldownMax;

        BarkShockwave wave;
        wave.shape.setRadius(10.f);
        wave.shape.setPosition(getPosition());
        wave.shape.setFillColor(sf::Color(255, 255, 255, 75));
        wave.shape.setOutlineColor(sf::Color(255, 255, 255, 100));
        wave.shape.setOutlineThickness(5.f);

        shockwaves.push_back(wave);
    }
}
// Expands the bark shockwave and fades it out
void Dog::UpdateBark(float deltaTime)
{
    if (barkCooldown > 0.f) barkCooldown -= deltaTime;

    for (auto iter = shockwaves.begin(); iter != shockwaves.end(); )
    {
		iter->shape.setPosition(getPosition());

        iter->lifetime -= deltaTime;

        float radius = iter->shape.getRadius() + iter->expandRate * deltaTime;
        iter->shape.setRadius(radius);
        iter->shape.setOrigin(radius, radius);

        auto c = iter->shape.getFillColor();
        c.a = static_cast<sf::Uint8>(std::max(0.f, c.a - iter->fadeSpeed * deltaTime));
        iter->shape.setFillColor(c);

        if (iter->lifetime <= 0)
            iter = shockwaves.erase(iter);
        else
            ++iter;
    }
}


void Dog::Draw(sf::RenderWindow& window)
{
	window.draw(dogBody);
}
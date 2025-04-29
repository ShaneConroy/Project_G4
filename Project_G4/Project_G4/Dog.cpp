#include "Dog.h"

Dog::Dog()
{
	dogHead.setRadius(12.f);
	dogHead.setOrigin(dogHead.getPosition().x + dogHead.getRadius(), dogHead.getPosition().y + dogHead.getRadius());
	dogHead.setFillColor(sf::Color(143, 85, 48));
	dogHead.setPosition(300, 300);

    // Dog Body
    dogBody.setRadius(18.f);
    dogBody.setFillColor(sf::Color(143, 85, 48));
    dogBody.setOrigin(dogBody.getRadius(), dogBody.getRadius());
    dogBody.setPosition(dogHead.getPosition());

    // Ears
    dogEarLeft.setRadius(6.f);
    dogEarLeft.setFillColor(sf::Color(143, 85, 48));
    dogEarLeft.setOrigin(dogEarLeft.getRadius(), dogEarLeft.getRadius());
    dogEarLeft.setPosition(dogHead.getPosition());

    dogEarRight.setRadius(6.f);
    dogEarRight.setFillColor(sf::Color(143, 85, 48));
    dogEarRight.setOrigin(dogEarRight.getRadius(), dogEarRight.getRadius());
    dogEarRight.setPosition(dogHead.getPosition());

    // Tail
    dogTail.setPointCount(4);
    dogTail.setPoint(0, sf::Vector2f(1.5f, -7.5f));  // Top center
    dogTail.setPoint(1, sf::Vector2f(15.f, 0.f));   // Right tip
    dogTail.setPoint(2, sf::Vector2f(1.5f, 7.5f));   // Bottom center
	dogTail.setPoint(3, sf::Vector2f(-20.f, 0.f));  // Left tip
    dogTail.setFillColor(sf::Color(143, 85, 48));
    dogTail.setPosition(dogBody.getPosition());

	// Snout
	dogSnout.setPointCount(6);
    dogSnout.setPoint(0, sf::Vector2f(0.f, 8.f));      // Bottom back
    dogSnout.setPoint(1, sf::Vector2f(-20.f, 8.f));  // Bottom tip
    dogSnout.setPoint(2, sf::Vector2f(-20.f, -8.f));   // Top tip
    dogSnout.setPoint(3, sf::Vector2f(0.f, -8.f));    // Top back
    dogSnout.setPoint(4, sf::Vector2f(5.f, -5.f));    // Upper notch
    dogSnout.setPoint(5, sf::Vector2f(5.f, 5.f));     // Lower notch
	dogSnout.setFillColor(sf::Color(143, 85, 48));
	dogSnout.setPosition(dogHead.getPosition());
}

void Dog::Update(sf::Vector2i mousePos)
{
	follow(mousePos);
}

void Dog::follow(sf::Vector2i mousePos)
{
    sf::Vector2f currentPos = dogHead.getPosition();
    sf::Vector2f targetPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    float speed = 0.01f;
 
    dogHead.setPosition(currentPos + speed * (targetPos - currentPos));

    // Update dogBody to follow behind dogHead
    sf::Vector2f dir = targetPos - currentPos;
    if (vectorLength(dir) > 0.01f)
    {
        dir = normaliseVector(dir);

        float bodyDistance = dogHead.getRadius() + dogBody.getRadius() - 7.5f;
        sf::Vector2f bodyPos = dogHead.getPosition() - dir * bodyDistance;
        dogBody.setPosition(lerp(dogBody.getPosition(), bodyPos, 0.4f));

        // Ears
        sf::Vector2f sideOffset(-dir.y, dir.x);
        float earBackOffset = 3.f;
        float earOffset = 12.f;
        sf::Vector2f earPosBase = dogHead.getPosition() - dir * earBackOffset;
        dogEarLeft.setPosition(earPosBase + sideOffset * earOffset);
        dogEarRight.setPosition(earPosBase - sideOffset * earOffset);

        // Tail
        float tailDistance = dogBody.getRadius() + 10.f;
        dogTail.setPosition(dogBody.getPosition() - dir * tailDistance);

        float tailAngle = atan2(dir.y, dir.x) * 180.f / 3.14159f;
        dogTail.setRotation(tailAngle + 180.f);

		// Snout
		float snoutOffsetDistance = dogHead.getRadius() + 1.5f;
		sf::Vector2f snoutOffset = normaliseVector(dir) * snoutOffsetDistance;
		dogSnout.setPosition(dogHead.getPosition() + snoutOffset);
		float snoutAngle = atan2(dir.y, dir.x) * 180.f / 3.14159f;
		dogSnout.setRotation(snoutAngle);

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
    window.draw(dogHead);
    window.draw(dogTail);
    window.draw(dogBody);
    window.draw(dogEarLeft);
    window.draw(dogEarRight);
	window.draw(dogSnout);
}
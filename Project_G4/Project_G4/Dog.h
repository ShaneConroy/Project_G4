#pragma once
#include "Global.h"
class Dog
{
public:
	Dog();

	void Update(sf::Vector2i mousePos);
	void Draw(sf::RenderWindow& window);

	// For making bark circle thingy
	struct BarkShockwave
	{
		sf::CircleShape shape;
		float lifetime = 0.2f;
		float fadeSpeed = 255.f;
		float maxRadius = 150.f;
		float expandRate = 600.f;
	};

	sf::Vector2f getPosition() { return dogBody.getPosition(); }
	const std::vector<BarkShockwave>& getShockwaves() const { return shockwaves; }

	void Bark();
	void UpdateBark(float deltaTime);

	bool barkTriggered = false;

private:

	void follow(sf::Vector2i mousePos);

	sf::CircleShape dogBody;

	std::vector<BarkShockwave> shockwaves;
	float barkCooldown = 0.f;
	float barkCooldownMax = 3.f;

};


#pragma once
#include "Global.h"

class Particle {
public:

    Particle(sf::Vector2f pos, sf::Vector2f vel, sf::Color color, float lifetime);

    void update(float dt);
    void draw(sf::RenderWindow& window) const;

    bool isDead() const;

private:

    sf::CircleShape shape;
    sf::Vector2f velocity;

    float lifetime;
    float maxLifetime;
};

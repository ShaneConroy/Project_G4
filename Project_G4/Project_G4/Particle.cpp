#include "Particle.h"

Particle::Particle(sf::Vector2f pos, sf::Vector2f vel, sf::Color color, float lifetime)
    : velocity(vel), lifetime(lifetime), maxLifetime(lifetime) {
    shape.setRadius(3.0f);
    shape.setFillColor(color);
    shape.setPosition(pos);
}

void Particle::update(float dt)
{
    // Move
    lifetime -= dt;
    shape.move(velocity * dt);

    // Fade out
    float alpha = std::max(0.f, lifetime / maxLifetime);
    sf::Color c = shape.getFillColor();
    c.a = static_cast<sf::Uint8>(255 * alpha);
    shape.setFillColor(c);
}

// If alive, draw
void Particle::draw(sf::RenderWindow& window) const 
{
    if (lifetime > 0) window.draw(shape);
}

bool Particle::isDead() const 
{
    return lifetime <= 0;
}

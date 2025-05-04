#pragma once

// For wool particles that pop out after shearing
struct WoolParticle
{
    sf::CircleShape shape;
    sf::Vector2f velocity;
    bool canCollect = false;
    float collectDelay = 1.f;
    Sheep* sourceSheep = nullptr;
};
#pragma once
#include "Global.h"
#include "ParticleType.h"
#include "Particle.h"

class ParticleManager {
public:
    void update(float dt);
    void draw(sf::RenderWindow& window);

    void emitFunc(sf::Vector2f position, ParticleType type);

private:
    std::vector<std::unique_ptr<Particle>> particles;

    void emitSheepDying(sf::Vector2f pos);
    void emitWolfDying(sf::Vector2f pos);
    void emitZombieDying(sf::Vector2f pos);
    void emitBuyingUpgrade(sf::Vector2f pos);
};


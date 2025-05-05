#include "ParticleManager.h"

void ParticleManager::update(float dt) 
{
    for (auto& p : particles) 
    {
        p->update(dt);
    }
    // Remove if ttl over
    particles.erase(std::remove_if(particles.begin(), particles.end(),
        [](const auto& p) { return p->isDead(); }), particles.end());
}

void ParticleManager::draw(sf::RenderWindow& window) 
{
    for (const auto& p : particles)
    {
        p->draw(window);
    }
}

void ParticleManager::emitFunc(sf::Vector2f pos, ParticleType type) 
{
    switch (type) 
    {
    case ParticleType::SheepDying: emitSheepDying(pos); break;
    case ParticleType::WolfDying: emitWolfDying(pos); break;
    case ParticleType::ZombieDying: emitZombieDying(pos); break;
    case ParticleType::BuyingUpgrade: emitBuyingUpgrade(pos); break;
    }
}

void ParticleManager::emitSheepDying(sf::Vector2f pos) 
{
    for (int i = 0; i < 33; ++i) 
    {
        sf::Vector2f vel(rand() % 2000 - 1000, rand() % 2000 - 1000);
        auto p = std::make_unique<Particle>(pos, vel * 0.1f, sf::Color::White, 1.0f);
        particles.push_back(std::move(p));
    }
}

void ParticleManager::emitWolfDying(sf::Vector2f pos) 
{
    for (int i = 0; i < 33; ++i)
    {
        sf::Vector2f vel(rand() % 1500 - 750, rand() % 1500 - 750);
        auto p = std::make_unique<Particle>(pos, vel * 0.25f, sf::Color(128, 21, 18), 0.25f);
        particles.push_back(std::move(p));
    }
}

void ParticleManager::emitZombieDying(sf::Vector2f pos) 
{
    for (int i = 0; i < 33; ++i) 
    {
        sf::Vector2f vel(rand() % 2500 - 1250, rand() % 2500 - 1250);
        auto p = std::make_unique<Particle>(pos, vel * 0.15f, sf::Color::Green, 1.0f);
        particles.push_back(std::move(p));
    }
}

void ParticleManager::emitBuyingUpgrade(sf::Vector2f pos) 
{
    for (int i = 0; i < 15; ++i) 
    {
        sf::Vector2f vel(0, -rand() % 100);
        auto p = std::make_unique<Particle>(pos, vel * 0.01f, sf::Color::Yellow, 0.8f);
        particles.push_back(std::move(p));
    }
}

#include "Global.h"

// Gets the distance between me and you
float getDistanceBetween(sf::Vector2f posOne, sf::Vector2f posTwo)
{
    float distance = std::sqrt(((posTwo.x - posOne.x) * (posTwo.x - posOne.x)) + ((posTwo.y - posOne.y) * (posTwo.y - posOne.y)));
    return distance;
}

sf::Vector2f normaliseVector(sf::Vector2f vec)
{
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length != 0) {
        return sf::Vector2f(vec.x / length, vec.y / length);
    }
    return vec;
}

sf::Vector2f randomPositionGlobalFunc(const sf::Vector2f& vec)
{
    std::random_device random;
    std::mt19937 randomInstance(random());
    std::uniform_real_distribution<float> distX(0.f, vec.x);
    std::uniform_real_distribution<float> distY(0.f, vec.y);

    float randomX = distX(randomInstance);
    float randomY = distY(randomInstance);

    return sf::Vector2f(randomX, randomY);
}
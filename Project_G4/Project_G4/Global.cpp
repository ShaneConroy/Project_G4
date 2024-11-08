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
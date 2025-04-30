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
    if (length != 0)
    {
        return sf::Vector2f(vec.x / length, vec.y / length);
    }
    return vec;
}

sf::Vector2f randomPosOnField(const sf::Vector2f& xRange, const sf::Vector2f& yRange) 
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distX(xRange.x, xRange.y);
    std::uniform_real_distribution<float> distY(yRange.x, yRange.y);

    return sf::Vector2f(distX(gen), distY(gen));
}

float vectorLength(const sf::Vector2f& vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t)
{
    return a + (b - a) * t;
}

int getNumberBetween(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(min, max);

    return dis(gen);
}

#pragma once
#include "Global.h"

class GrassUtility
{
public:
    template <typename T>
    static sf::Vector2f FindClosestNodePosition(const sf::Vector2f& sheepPosition, const std::vector<T>& grassNodeArray);
};


// Loop through the grassNode array and find the closest position
template <typename T>
sf::Vector2f GrassUtility::FindClosestNodePosition(const sf::Vector2f& sheepPosition, const std::vector<T>& grassNodeArray)
{
    float currentClosest = FLT_MAX;
    sf::Vector2f closestPos;

    for (const auto& grassNode : grassNodeArray)
    {
		float gnX = grassNode.x;
		float gnY = grassNode.y;
		sf::Vector2f gnPos = { gnX, gnY };

        float newClosest = getDistanceBetween(sheepPosition, gnPos);
        if (newClosest < currentClosest)
        {
            currentClosest = newClosest;
            closestPos = gnPos;
        }
    }

    return closestPos;
}

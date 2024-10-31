#pragma once
#include "Global.h"

// The world will control the fence, maybe spawning of grass nodes, day/night cycle

// Currently the dyalight cycle goes from light green (day) to night but doesnt go back to day.
// A solution to this could be having a button "Next day?" And when you press it, it resets to day

// Day -> (134, 172, 19)
// Night -> (40, 108, 89)

class World
{
private:

	float transition = 0.0f;

public:

	sf::Color DaylightCycle();

};


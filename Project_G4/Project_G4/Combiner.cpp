#include "Combiner.h"

// Sorts the flock vector by who has most greateness, then takes the top 4 best sheep and combines them into one
void Combiner::Combine(std::vector<Sheep>& topFour, std::vector<Sheep>& flock)
{
	std::cout << "Combining..." << std::endl;

	// Reset variables
	Sheep::sheepStats newStats{};
	newStats.greatness = 0;
	newStats.timeAlive = 0.f;
	newStats.timeCLoseToWolf = 0.f;
	newStats.canReproduce = true;
	newStats.deaf = false;
	newStats.goldenSheep = false;
	newStats.walkSpeed = 45.0f;
	newStats.eatSpeed = 5.0f;
	newStats.woolBonus = 50;
	newStats.bodySize = 15;
	newStats.awarness = 2.0f;
	newStats.fear = 100.f;

	// Finds the highest prestige in the top 4 and increments the new sheeps prestige based off that
	int highestPrestige = 0;
	for (const Sheep& s : topFour)
	{
		highestPrestige = std::max(highestPrestige, s.myStats.prestige);
	}
	newStats.prestige = std::min(highestPrestige + 1, 4); // Cap at 4


	float totalGreatness = 0;
	for (const Sheep& sheep : topFour)
	{
		totalGreatness += sheep.getGreatness();
	}

	// Gets the true value of each stat based off the top 4 sheep
	auto getWeightofStat = [&](auto Stat)
		{
			float trueValue = 0;

			for (auto& sheep : topFour)
			{
				float weight = sheep.getGreatness() / totalGreatness;
				trueValue += Stat(sheep) * weight;
			}
			return trueValue;
		};

	// Set all stats with new true value stats
	newStats.walkSpeed = getWeightofStat([](const Sheep& sheep) {return sheep.myStats.walkSpeed;});
	newStats.eatSpeed = getWeightofStat([](const Sheep& sheep) {return sheep.myStats.eatSpeed;});
	newStats.woolBonus = getWeightofStat([](const Sheep& sheep) {return sheep.myStats.woolBonus;});
	newStats.bodySize = getWeightofStat([](const Sheep& sheep) {return sheep.myStats.bodySize;});
	newStats.awarness = getWeightofStat([](const Sheep& sheep) {return sheep.myStats.awarness;});
	newStats.fear = getWeightofStat([](const Sheep& sheep) {return sheep.myStats.fear;});

	int mutationRoll = getNumberBetweenInt(1, 100);
	if (mutationRoll <= 5)
	{
		std::cout << "Mutation occurred! Sheep is infected." << std::endl;
		newStats.infected = true;
	}

	Sheep combinedSheep(newStats);
	std::cout << "New sheep created..." << std::endl;
	flock.push_back(combinedSheep);
	std::cout << "New sheep in array." << std::endl;
}


#include "Combiner.h"

// Sorts the flock vector by who has most greateness, then takes the top 4 best sheep and combines them into one
void Combiner::Combine(std::vector<Sheep>& flock)
{

	std::cout << "Combining sheep..." << std::endl;

	sortByGreatness(flock);

	std::vector<Sheep> topSheep(flock.begin(), flock.begin() + 4); // Get top 4 greatest sheep
	for (int i = 0; i < 4; ++i)
	{
		flock[i].myStats.prestige += 1;
	}

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

	float totalGreatness = 0;
	for (const Sheep& sheep : topSheep)
	{
		totalGreatness += sheep.getGreatness();
	}

	// Gets the true value of each stat based off the top 4 sheep
	auto getWeightofStat = [&](auto Stat)
		{
			float trueValue = 0;

			for (auto& sheep : topSheep)
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

	Sheep combinedSheep(newStats);
	std::cout << "New sheep created..." << std::endl;
	flock.push_back(combinedSheep);
	std::cout << "New sheep in array." << std::endl;
}

// Sorts the array so the greatess sheep is first
void Combiner::sortByGreatness(std::vector<Sheep>& flock)
{
	std::cout << "Sorting array..." << std::endl;

	std::sort(flock.begin(), flock.end(), [](const Sheep& a, const Sheep& b) {
		return a.getGreatness() > b.getGreatness();
		});
}


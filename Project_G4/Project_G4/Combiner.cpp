#include "Combiner.h"

// Sorts the flock vector by who has most greateness, then takes the top 4 best sheep and combines them into one
void Combiner::Combine(std::vector<Sheep>& flock)
{
	for (Sheep& sheep : flock)
	{
		sheep.setColour(sf::Color::Red);
	}

	std::cout << "Combining sheep..." << std::endl;
	// Sort top 4
	std::sort(flock.begin(), flock.end(), [](const Sheep& a, const Sheep& b) {
		return a.getGreatness() > b.getGreatness();
		});
	std::vector<Sheep> topSheep(flock.begin(), flock.begin() + 4);

	Sheep combinedSheep;

	// Reset variables
	Sheep::sheepStats newStats{};
	newStats.greatness = 0;
	newStats.timeAlive = 0.f;
	newStats.timeCLoseToWolf = 0.f;
	newStats.canReproduce = true;
	newStats.deaf = false;
	newStats.walkSpeed = 45.0f;
	newStats.eatSpeed = 5.0f;
	newStats.woolBonus = 50;
	newStats.bodySize = 15;
	newStats.awarness = 2.0f;
	newStats.fear = 100.f;



}

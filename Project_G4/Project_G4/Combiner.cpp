#include "Combiner.h"

// This will take all the sheep and combine the top 4 into one
void Combiner::Combine(std::vector<Sheep>& flock)
{
	// Sorts the flock vector by who has most greateness
	std::sort(flock.begin(), flock.end(), [](const Sheep& a, const Sheep& b) {
		return a.getGreatness() > b.getGreatness();
		});
	// Then takes the top 4 best sheep
	std::vector<Sheep> topSheep(flock.begin(), flock.begin() + 4);

	// Then combines them into one sheep
	Sheep combinedSheep;
	Sheep::sheepStats newStats = { 0 };


}

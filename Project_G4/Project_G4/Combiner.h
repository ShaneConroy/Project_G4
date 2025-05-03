#pragma once
#include "Global.h"
#include "Sheep.h"

class Combiner
{
public:

	void Combine(std::vector<Sheep>& flock);

private:

	void sortByGreatness(std::vector<Sheep>& flock);

};


#include "World.h"

// When called this function will spawn grass nodes randomly around the field
void World::SpawnGrassNodes()
{
    if (econ.fertiliserPurchased)
    {
        grassNodeArray.emplace_back();
		econ.fertiliserPurchased = false;
    }
}

// Fills an array with only the grass nodes that are not taken // TODO Turn into list so its better ofr performance
std::vector< sf::Vector2f> World::UpdateGrassNodes()
{
    std::vector<sf::Vector2f> availableGrassNodesPos;

    auto iter = grassNodeArray.begin();

    while (iter != grassNodeArray.end())
    {
        if (iter->CheckEaten())
        {
            iter = grassNodeArray.erase(iter);
        }
        else
        {
            if (!iter->CheckTaken())
            {
                availableGrassNodesPos.push_back(iter->getPosition());
            }
            ++iter;
        }
    }
    return availableGrassNodesPos;
}

// Passes the grass node array into the find grass noode function
void World::PassGrassToSheep()
{
    for (Sheep& sheep : sheepArray)
    {
        for (Grass& grass : grassNodeArray)
        {
            if (getDistanceBetween(sheep.getPosition(), grass.getPosition()) < 6.0)
            {
                sheep.setBehaviour(behaviours::eating);
				grass.UpdateTaken(true);

                if (sheep.doneEating)
                {
					grass.UpdateEaten(true);
                }
            }
        }
    }
}

// Updates the grass colour of the fenced area to match the rest of the world
void World::updateFencedGrass()
{
    sf::Color newColour = DaylightCycle();
    fence.UpdateGrass(newColour);
}

// Adds the sheep to the world
void World::PopulateWorldWithSheep()
{
    // When a sheep is bought, add a sheep in
    if (econ.sheepPurchased)
	{
		sheepArray.emplace_back();
		econ.sheepPurchased = false;
	}
    // If a sheep is sold, pop one out
    if (econ.sheepSold) // TODO // firgue ts out
    {
        if (sheepArray.size() > 1)
        {
            sheepArray.pop_back();
			econ.addFunds(Funds_Enum::sheepSold);
        }
        econ.sheepSold = false;
    }
}


int World::WorldTime()
{
    if (isDay)
    {
        currentTime += 1;
        if (currentTime >= 3334)
        {
            isDay = false;
        }
    }
    if (!isDay)
    {
        currentTime -= 1;
        if (currentTime <= 0)
        {
            isDay = true;
        }
    }

    return currentTime;
}

// Based on the time, returns a RGB value
sf::Color World::DaylightCycle()
{
    sf::Color dayColor = { 134, 172, 19 };
    sf::Color nightColor = { 40, 108, 89 };
    sf::Color newColour;

    transition = static_cast<float>(currentTime) / 3334;

    float r = dayColor.r + transition * (nightColor.r - dayColor.r);
    float g = dayColor.g + transition * (nightColor.g - dayColor.g);
    float b = dayColor.b + transition * (nightColor.b - dayColor.b);

    // Error with "narrowing conversion." The static_cast was ChatGPTs solution
    newColour = { static_cast<sf::Uint8>(r),
                  static_cast<sf::Uint8>(g),
                  static_cast<sf::Uint8>(b) };

    return newColour;
}

void World::Draw(sf::RenderWindow& window)
{
    window.draw(bg);

    for (const Grass& grass : grassNodeArray)
    {
        window.draw(grass.grassNode);
    }

    fence.Draw(window);

    for (Sheep& sheep : sheepArray)
    {
        sheep.Draw(window);
    }
}

void World::Update(float deltaTime, sf::Vector2i mousePos)
{

    // When the gate is closed, sheep inside will not update
    for (Sheep& sheep : sheepArray)
    {
        if (fence.gateOpen)
        {
            sheep.Update(deltaTime, fence.getRect(), UpdateGrassNodes());
        }
        else
        {
            if (!fence.getRectArea().getGlobalBounds().contains(sheep.getPosition()))
            {
                sheep.Update(deltaTime, fence.getRect(), UpdateGrassNodes());
            }
        }
    }

    fence.gateFunction(mousePos);
    PopulateWorldWithSheep();
    PassGrassToSheep();
    UpdateGrassNodes();
    SpawnGrassNodes();
    econ.calculatePassiveIncome(static_cast<int>(sheepArray.size()));
    econ.sellSheep(mousePos);
    econ.buySheep(mousePos);
}

void World::FixedUpdate()
{
    bg.setFillColor(DaylightCycle());
    updateFencedGrass();
    WorldTime();
    econ.update();
}

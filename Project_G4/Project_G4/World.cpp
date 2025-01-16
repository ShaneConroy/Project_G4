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

// Fills an array with only the grass nodes that are not taken 
std::vector<Grass> World::UpdateGrassNodes()
{
    std::vector<Grass> availableGrassNodes;

    for (auto grass = grassNodeArray.begin(); grass != grassNodeArray.end(); ++grass)
    {
        if (grass->CheckTaken())
        {
            continue;
        }

        availableGrassNodes.push_back(*grass);
    }

    grassNodeArray.clear();

    for (const auto& grass : availableGrassNodes)
    {
        grassNodeArray.push_back(grass);
    }

    return grassNodeArray;
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
    if(econ.sheepPurchased)
	{
		sheepArray.emplace_back();
		econ.sheepPurchased = false;
	}
    // If a sheep is sold, pop one out
    if (econ.sheepSold)
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

// Passes the grass node array into the find grass noode function
void World::PassGrassToSheep()
{
	for (Sheep& sheep : sheepArray)
	{
		sheep.FindGrassNode(UpdateGrassNodes());
	}
}

void World::Update(float deltaTime, sf::Vector2i mousePos)
{

    for (Sheep& sheep : sheepArray)
    {
        if (fence.gateOpen)
        {
			sheep.Update(deltaTime, fence.getRect());
		}
        else
        {
            if (!fence.getRectArea().getGlobalBounds().contains(sheep.getPosition()))
            {
                sheep.Update(deltaTime, fence.getRect());
            }
        }

    }

    fence.gateFunction(mousePos);
    PopulateWorldWithSheep();
    PassGrassToSheep();
    UpdateGrassNodes();
    SpawnGrassNodes();
    econ.calculatePassiveIncome(sheepArray.size());
}

void World::FixedUpdate()
{
    bg.setFillColor(DaylightCycle());
    updateFencedGrass();
    WorldTime();
    econ.update();
}

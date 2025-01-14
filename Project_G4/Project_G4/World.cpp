#include "World.h"

// When called this function will spawn grass nodes randomly around the field
void World::SpawnGrassNodes()
{
    for (int iter = 0; iter < GRASS_CAP; iter++)
    {
        grassNodeArray.emplace_back();
    }
}

// Updates the grass nodes
void World::UpdateGrassNodes()
{
    float distance;
    for (Grass& grass : grassNodeArray)
    {
        for (Sheep& sheep : sheepArray)
        {
            distance = getDistanceBetween(sheep.getPosition(), grass.getPosition());

            if (distance < 5)
            {
                grass.UpdateTaken(true);
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

// Adds the shee[p to the world
void World::PopulateWorldWithSheep()
{
    for (int iter = 0; iter < SHEEP_CAP; iter++)
    {
        sheepArray.emplace_back();
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
    std::vector<Grass> availableGrassNodes;
    for (Grass grass : grassNodeArray)
    {
        if (!grass.CheckTaken())
        {
            availableGrassNodes.push_back(grass);
        }
    }

    for (auto sheep = sheepArray.begin(); sheep != sheepArray.end(); sheep++)
    {
        if (!availableGrassNodes.empty())
        {
            sheep->FindGrassNode(availableGrassNodes);
        }

        for (auto grass = grassNodeArray.begin(); grass != grassNodeArray.end();)
        {
            if (grass->CheckTaken())
            {
                ++grass;
                continue;
            }
            else if (getDistanceBetween(sheep->getPosition(), grass->getPosition()) < 5.f)
            {
                sheep->setBehaviour(behaviours::idle); // TODO // set to eating
                break;
            }

            ++grass;
        }

        if (grassNodeArray.empty())
        {
            sheep->setBehaviour(behaviours::idle);
        }
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
}

void World::FixedUpdate()
{
    bg.setFillColor(DaylightCycle());
    PassGrassToSheep();
    UpdateGrassNodes();
    WorldTime();
    updateFencedGrass();
}

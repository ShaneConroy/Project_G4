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

            if (distance < 15)
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
    if (currentTime > 0) // not night
    {
         currentTime -= 1;
    }
   
    std::cout << "Time: " << currentTime << "\n";

    return currentTime;
}

// Based on the time, returns a RGB value
sf::Color World::DaylightCycle()
{
    sf::Color dayColor = { 134, 172, 19 };
    sf::Color nightColor = { 40, 108, 89 };
    sf::Color newColour;

    transition = std::min(1.0f, transition + 0.00015f); // Day is 55~ seconds & 3334 frames (1667 now)

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
    for (auto sheep = sheepArray.begin(); sheep != sheepArray.end();)
    {
        for (auto grass = grassNodeArray.begin(); grass != grassNodeArray.end();)
        {
            if (grass->CheckTaken() && WorldTime()) // == 0) // Check if the current grass node is taken
            {
                grass = grassNodeArray.erase(grass);
            }
            else {
                sheep->FindGrassNode(grassNodeArray);
                grass++;
            }
        }
        sheep++;
    }
}

void World::Update(float deltaTime)
{
    for (Sheep& sheep : sheepArray)
    {
        sheep.Update(deltaTime);
    }
    
}

void World::FixedUpdate()
{
    bg.setFillColor(DaylightCycle());
    PassGrassToSheep();
    UpdateGrassNodes();
    WorldTime();
    updateFencedGrass();
}

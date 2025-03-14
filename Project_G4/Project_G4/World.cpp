#include "World.h"

// When called this function will spawn grass nodes randomly around the field
void World::SpawnGrassNodes()
{
    if (econ.fertiliserPurchased)
    {
        for (int i = 0; i < grassBuyAmount; i++)
        {
            grassNodeArray.emplace_back();
        }
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

// Passes the grass node array into the find grass noode function // TODO // This will have to change
void World::PassGrassToSheep()
{
    std::vector<sf::Vector2f> availableGrassPositions = UpdateGrassNodes();

    // Pass the updated grass positions to each sheep
    for (Sheep& sheep : sheepArray)
    {
        if (sheep.isLeader)
        {
            sheep.availibleGrass(availableGrassPositions);
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
   
    if (econ.sheepPurchased)
    {
        // When a sheep is bought, add a sheep in
        if (sheepArray.size() < sheepCap)
        {
            sheepArray.emplace_back();
        }
        else // If the max is to be exceeded, refund
        {
            econ.addFunds(Funds_Enum::refund);
        }
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

// Updates how many sheep the player can have at one time
void World::up_SheepMax()
{
    if (econ.up_MaxSheepBool)
    {
        sheepCap = (sheepCap * 2);
        econ.up_MaxSheepBool = false;

        // Change barn looks
        if (econ.barnLevel == 1)
            econ.upgradeBarn(sf::IntRect(398, 0, 386, 154));
        else if(econ.barnLevel == 2)
            econ.upgradeBarn(sf::IntRect(807, 0, 386, 135));
        else if(econ.barnLevel == 3)
            econ.upgradeBarn(sf::IntRect(1219, 0, 387, 142));
    }
}

void World::up_WoolSell()
{
    if (econ.up_WoolSellPrice)
    {
        if (econ.loomLevel == 1)
            std::cout << "Loom Level one" << "\n";
        else if(econ.loomLevel == 2)
            std::cout << "Loom Level two" << "\n";
        else if(econ.loomLevel == 3)
            std::cout << "Loom Level three" << "\n";
    }
}

void World::up_SheepAmount()
{
    if (econ.up_SheepAmountBool)
    {
        if (econ.marketLevel == 1)
            std::cout << "Market Level one" << "\n";
        else if (econ.marketLevel == 2)
            std::cout << "Market Level two" << "\n";
        else if (econ.marketLevel == 3)
            std::cout << "Market Level three" << "\n";
    }
}

void World::up_GrassAmount()
{
    if (econ.up_GrassAmountBool)
    {
        if (econ.gardenLevel == 1)
            std::cout << "Garden Level one" << "\n";
        else if (econ.gardenLevel == 2)
            std::cout << "Garden Level two" << "\n";
        else if (econ.gardenLevel == 3)
            std::cout << "Garden Level three" << "\n";
    }
}

int World::WorldTime()
{
    if (isDay)
    {
        currentTime += 1;
        if (currentTime >= timeInDay)
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

    transition = static_cast<float>(currentTime) / timeInDay;

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
    econ.draw(window, econ.popOpen);
}

void World::Update(float deltaTime, sf::Vector2i mousePos)
{
    // Assign Leader
    if (!sheepArray.empty())
    {
        sheepArray.front().isLeader = true;
    }
    // When the gate is closed, sheep inside will not update
    for (Sheep& sheep : sheepArray)
    {
        if (fence.gateOpen)
        {
            sheep.Update(deltaTime, fence.getRect(), fence.getRectArea(), UpdateGrassNodes(), sheepArray);
        }
        else
        {
            if (!fence.getRectArea().getGlobalBounds().contains(sheep.getPosition()))
            {    
                sheep.Update(deltaTime, fence.getRect(), fence.getRectArea(), UpdateGrassNodes(), sheepArray);
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
	econ.buyGrass(mousePos);
    econ.popOutPanelFunc(mousePos);
    econ.upgradeMaxSheep(mousePos);
    econ.upgradeWoolPrice(mousePos);
    econ.upgradeSheepPurchaseAmount(mousePos);
    econ.upgradeGrassPurchaseAmount(mousePos);

    up_SheepMax();
    up_WoolSell();
    up_SheepAmount();
    up_GrassAmount();
}

void World::FixedUpdate()
{
    bg.setFillColor(DaylightCycle());
    updateFencedGrass();
    WorldTime();
    econ.update();
}

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

// Fills an array with only the grass nodes that are not taken
std::vector<sf::Vector2f> World::UpdateGrassNodes()
{
    std::vector<sf::Vector2f> availableGrassNodesPos;
    auto iter = grassNodeArray.begin();

    while (iter != grassNodeArray.end())
    {
        bool grassClaimed = false;

        for (Sheep& sheep : sheepArray)
        {
            float dist = getDistanceBetween(sheep.getPosition(), iter->getPosition());

            // Claim a grass node if close enough and not already eating
            if (dist < 10.f && !iter->CheckTaken() && !sheep.isEating)
            {
                iter->UpdateTaken(true);                     // Mark grass as taken
                sheep.isEating = true;                       // Sheep enters eating state
                sheep.myStats.eatSpeed = 5.0f;                 // Reset timer
                sheep.lastEatenGrass = iter->getPosition();  // Track which grass it's eating
                grassClaimed = true;
                break; // Only one sheep should claim it
            }

            // If the sheep is done eating this exact node
            if (sheep.doneEating && sheep.lastEatenGrass == iter->getPosition())
            {
                iter->UpdateEaten(true);     // Grass is now eaten
                sheep.doneEating = false;    // Reset sheep flag
                grassClaimed = true;         // Skip this node for others
                break;
            }
        }

        if (iter->CheckEaten())
        {
            iter = grassNodeArray.erase(iter); // Safely erase eaten grass
        }
        else
        {
            if (!iter->CheckTaken())
            {
                availableGrassNodesPos.push_back(iter->getPosition()); // Still usable
            }

            ++iter;
        }
    }

    return availableGrassNodesPos;
}

// Passes the grass node array into the find grass noode function
void World::PassGrassToSheep()
{
    std::vector<sf::Vector2f> availableGrassPositions = UpdateGrassNodes();

    // Pass the updated grass positions to each sheep
    for (Sheep& sheep : sheepArray)
    {
        sheep.availibleGrass(availableGrassPositions);
    }
}

// Spwans the wolf cash orb with the wool particle system
void World::spawnCashOrb(const WoolParticle& orb)
{
    woolParticles.push_back(orb);
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
            for (int i = 0; i < sheepBuyAmount; i++)
            {
                sheepArray.emplace_back();
                herd.push_back(&sheepArray.back());
            }
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
            particleSpawner.emitFunc(sheepArray.back().getPosition(), ParticleType::SheepDying);
            sheepArray.pop_back();
			herd.pop_back();
			econ.addFunds(Funds_Enum::sheepSold);
        }
        econ.sheepSold = false;
    }

    // Refresh to advoid weird bug
    herd.clear();
    for (auto& sheep : sheepArray)
    {
        herd.push_back(&sheep);
    }
    if (wolf)
    {
        wolf->clearTarget(); // Refreshes wolf's memory lol
    }

}

// Spawns a wolf at one of the edges of the screen
void World::spawnWolf()
{
    int randNum = rand() % 3;
    wolf.emplace(randNum);
}

// Updates how many sheep the player can have at one time
void World::up_SheepMax()
{
    if (econ.up_MaxSheepBool && econ.barnLevel != maxUp_sheepCap)
    {
        sheepCap = (sheepCap * 2);
        econ.up_MaxSheepBool = false;

        // Change barn looks
        if (econ.barnLevel == 1)
            econ.upgradeBarn(sf::IntRect(176, 0, 151, 87));
        else if (econ.barnLevel == 2)
            econ.upgradeBarn(sf::IntRect(363, 0, 150, 75));
        else if (econ.barnLevel == 3)
            econ.upgradeBarn(sf::IntRect(544, 0, 150, 76));
        else if (econ.barnLevel == 4)
            econ.upgradeBarn(sf::IntRect(701, 0, 152, 77));
    }
}

void World::up_WoolSell()
{
    if (econ.up_WoolSellPrice && econ.loomLevel != maxUp_woolSell)
    {
        econ.woolSellPrice = static_cast<int>(econ.woolSellPrice * 0.33f);
        econ.up_WoolSellPrice = false;

        if (econ.loomLevel == 1)
            econ.upgradeLoom(sf::IntRect(135, 0, 138, 75));
        else if (econ.loomLevel == 2)
            econ.upgradeLoom(sf::IntRect(288, 0, 139, 75));
        else if (econ.loomLevel == 3)
            econ.upgradeLoom(sf::IntRect(440, 0, 140, 75));
        else if (econ.loomLevel == 4)
            econ.upgradeLoom(sf::IntRect(599, 0, 140, 75));
    }
}

void World::up_SheepAmount()
{
    if (econ.up_SheepAmountBool && econ.marketLevel != maxUp_sheepAmount)
    {
        if (econ.marketLevel == 1)
        {
            econ.upgradeMarket(sf::IntRect(165, 0, 148, 75));
            sheepBuyAmount = 2;
        }
        else if (econ.marketLevel == 2)
        {
            econ.upgradeMarket(sf::IntRect(334, 0, 148, 75));
            sheepBuyAmount = 3;
        }
        else if (econ.marketLevel == 3)
        {
            econ.upgradeMarket(sf::IntRect(500, 0, 148, 75));
            sheepBuyAmount = 4;
        }
        else if(econ.marketLevel == 4)
        {
            econ.upgradeMarket(sf::IntRect(661, 0, 148, 75));
            sheepBuyAmount = 5;
        }
    }
}

void World::up_GrassAmount()
{
    if (econ.up_GrassAmountBool && econ.gardenLevel != maxUp_grassAmount)
    {
        if (econ.gardenLevel == 1)
        {
            econ.upgradeGarden(sf::IntRect(160, 0, 130, 75));
            grassBuyAmount = 2;
        }
        else if (econ.gardenLevel == 2)
        {
            econ.upgradeGarden(sf::IntRect(313, 0, 139, 75));
            grassBuyAmount = 3;
        }
        else if (econ.gardenLevel == 3)
        {
            econ.upgradeGarden(sf::IntRect(474, 0, 145, 75));
            grassBuyAmount = 4;
        }
        else if(econ.gardenLevel == 4)
        {
            econ.upgradeGarden(sf::IntRect(640, 0, 147, 75));
            grassBuyAmount = 5;
        }
    }
}

// If shears are on, click mouse on sheep to shear em
void World::shearsFunc(sf::Vector2i mousePos)
{
    if (econ.shearsOn)
    {
        for (Sheep& sheep : sheepArray)
        {
            sf::FloatRect body = sheep.getBody();

            if (mousePos.x >= body.left && mousePos.x <= body.left + body.width &&
                mousePos.y >= body.top && mousePos.y <= body.top + body.height)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (isDay)
                    {
                        sf::Vector2f centerOfSheep = sheep.getPosition();

                        // Creatinf wool particles
                        for (int i = 0; i < sheep.amountEaten; ++i)
                        {
                            WoolParticle woolParticle;
                            woolParticle.shape.setRadius(10.f);
                            woolParticle.shape.setFillColor(sf::Color::White);
                            woolParticle.shape.setPosition(centerOfSheep);
                            woolParticle.sourceSheep = &sheep; // Get the sheep it originated from for selling

                            // Get random angle and speed
                            float angle = static_cast<float>((rand() % 360) * (3.14159 / 180.f));
                            float speed = static_cast<float>((rand() % 30) + 50);
                            woolParticle.velocity = { cos(angle) * speed, sin(angle) * speed };

                            woolParticles.push_back(woolParticle);
                        }

                        if (!sheep.myStats.goldenSheep)
                        {
                            sheep.setColour(sf::Color::White);
                        }
                        if (sheep.myStats.prestige == 0)
                        {
                            sheep.setColour(sf::Color(255, 215, 0));
                        }
                        else if (sheep.myStats.prestige == 1)
                        {
                            sheep.setColour(sf::Color(188, 230, 255));
                        }
                        else if (sheep.myStats.prestige == 2)
                        {
                            sheep.setColour(sf::Color(214, 6, 32));
                        }
                        else if (sheep.myStats.prestige == 3)
                        {
                            sheep.setColour(sf::Color(249, 166, 50));
                        }
                        else if (sheep.myStats.prestige == 4)
                        {
                            sheep.setColour(sf::Color(255, 192, 203));
                        }

                        sheep.amountEaten = 0;
                        sheep.setRadius(sheep.myStats.bodySize);
                    }
                }

            }
        }
    }
	// Completly optional, but if the shears are off, clicking on a sheep will give you a heart
    else if (!econ.shearsOn)
    {
        for (Sheep& sheep : sheepArray)
        {
            sf::FloatRect body = sheep.getBody();

            if (body.contains(static_cast<sf::Vector2f>(mousePos)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sheepHeartCooldown <= 0.f)
                {
                    sf::Vector2f pos = sheep.getPosition();

                    FloatingText heartText;
                    heartText.text.setFont(Font);
                    heartText.text.setString("<3");
                    heartText.text.setCharacterSize(25);
                    heartText.text.setFillColor(sf::Color::White);
                    heartText.text.setPosition(pos + sf::Vector2f(0.f, -15.f));
                    heartText.velocity = sf::Vector2f(0.f, -20.f);

                    floatingTexts.push_back(heartText);

                    sheepHeartCooldown = sheepHeartCooldownCap;
                }
            }
        }
    }
}

// Updates time of day, changes the bool
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

    // Error with "narrowing conversion." The static_cast<sf::Uint8> was ChatGPTs solution
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

    particleSpawner.draw(window);

    for (Sheep& sheep : sheepArray)
    {
        sheep.Draw(window);
    }

    for (const WoolParticle& wool : woolParticles)
    {
        window.draw(wool.shape);
    }

    for (const auto& ft : floatingTexts)
    {
        window.draw(ft.text);
    }

    for (const auto& wave : dog.getShockwaves())
    {
        window.draw(wave.shape);
    }

    if (wolf)
        wolf->Draw(window);
    dog.Draw(window);

    econ.draw(window, econ.popOpen);

    if (showHoverText)
    {
        window.draw(upgradeText);
    }

	window.draw(combinerSprite);



}

void World::Update(float deltaTime, sf::Vector2i mousePos)
{
    // Leader
    int currentLeaderIndex = -1;
    for (int i = 0; i < sheepArray.size(); ++i)
    {
        if (sheepArray[i].isLeader)
        {
            currentLeaderIndex = i;
            break;
        }
    }
    if (currentLeaderIndex != -1 && sheepArray[currentLeaderIndex].isEating)
    {
        sheepArray[currentLeaderIndex].isLeader = false;

        for (int i = currentLeaderIndex + 1; i < sheepArray.size(); ++i)
        {
            if (!sheepArray[i].isEating)
            {
                sheepArray[i].isLeader = true;
                break;
            }
        }
    }

    bool leaderExists = false;
    for (Sheep& sheep : sheepArray)
    {
        if (sheep.isLeader)
        {
            leaderExists = true;
            break;
        }
    }
    if (!leaderExists && !sheepArray.empty())
    {
        sheepArray.front().isLeader = true;
    }

    if (wolf.has_value())
        wolfPos = wolf->getPosition();

    // Sheep Updates
    for (Sheep& sheep : sheepArray)
    {
        // If the gate is open or sheep is outside the pen
        if (fence.gateOpen || !fence.getRectArea().getGlobalBounds().contains(sheep.getPosition())) // Note to self: If wolf ever gives weird error, I removed the check here
        {
            sheep.Update(deltaTime, fence.getRect(), fence.getRectArea(), UpdateGrassNodes(), sheepArray, dog.getPosition(), wolfPos);
        }

        // Emergency teleport button if stuck
        if (econ.stuck)
        {
            sheepArray.front().setPosition({ 600.f, 300.f });
            econ.stuck = false;
        }

        // Handle whistle
        if (econ.whistle)
        {
            for (Sheep& sheep : sheepArray)
            {
                if (!sheep.myStats.deaf)
                {
                    sheep.whistleDelay = sheep.myStats.awarness; // Start countdown based on awareness
                }
            }
            econ.whistle = false;
        }


        // Spawn wolf at night
        if (!isDay && wolvesAbout == 0)
        {
            spawnWolf();
            wolvesAbout++;
        }
        else if (isDay && wolvesAbout > 0)
        {
            if (wolf)
            {
                wolf.reset(); // TODO // Maybe make this look nicer
            }
            wolvesAbout = 0;
        }

        // If a sheep is close to a wolf, add 1 to that sheeps gretaness
        if (wolf)
        {
            if (getDistanceBetween(sheep.getPosition(), wolf->getPosition()) >= 25.f)
            {
                closeTimer += deltaTime;
                if (closeTimer >= 1.0f)
                {
                    sheep.setGreatness(1);
                }

            }
        }

    } // for

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        dog.Bark();
    }
    dog.UpdateBark(deltaTime);

    if (wolf && dog.barkTriggered)
    {
        sf::Vector2f wolfPos = wolf->getPosition();
        sf::Vector2f dogPos = dog.getPosition();
        float dist = getDistanceBetween(dogPos, wolfPos);

        if (dist < 200.f)
        {
            wolf->setStunned(0.75f);
        }

        dog.barkTriggered = false;
    }

    if (wolf)
        wolf->Hunt(herd, deltaTime, getInnerFence(), this);

    for (auto iter = sheepArray.begin(); iter != sheepArray.end(); )
    {
        if (iter->eatenByWolf)
        {
            if (iter->myStats.infected)
            {
                particleSpawner.emitFunc(iter->getPosition(), ParticleType::ZombieDying);
            }
            else {
                particleSpawner.emitFunc(iter->getPosition(), ParticleType::SheepDying);
            }
            iter = sheepArray.erase(iter);
        }
        else
        {
            ++iter;
        }
    }

	shearsFunc(mousePos);

    fence.gateFunction(mousePos);

    PopulateWorldWithSheep();
    PassGrassToSheep();
    UpdateGrassNodes();
    SpawnGrassNodes();

    //econ.calculatePassiveIncome(static_cast<int>(sheepArray.size()));
    econ.stuckButtonFunc(mousePos);
    econ.sellSheep(mousePos);
    econ.buySheep(mousePos);
    econ.buyGrass(mousePos);
    econ.popOutPanelFunc(mousePos);
    econ.upgradeMaxSheep(mousePos);
    econ.upgradeWoolPrice(mousePos);
    econ.upgradeSheepPurchaseAmount(mousePos);
    econ.upgradeGrassPurchaseAmount(mousePos);
    econ.whistleButtonFunc(mousePos);
	econ.shearsButtonFunc(mousePos);
	econ.combineButtonFunc(mousePos);

    up_SheepMax();
    up_WoolSell();
    up_SheepAmount();
    up_GrassAmount();

    particleSpawner.update(deltaTime);

    if (econ.popOpen)
    {
        displayCosts(mousePos);
    }

	// Update for wool particles. In charge of moving and collection
    sf::Vector2f mouseFloatPos = static_cast<sf::Vector2f>(mousePos);

    for (auto it = woolParticles.begin(); it != woolParticles.end(); )
    {
        if (it->collectDelay > 0.f)
        {
            it->collectDelay -= deltaTime;
            it->shape.move(it->velocity * deltaTime);
            it->velocity *= .99f;
            ++it;
            continue;
        }

        it->canCollect = true;

        sf::Vector2f toMouse = mouseFloatPos - it->shape.getPosition();
        float dist = vectorLength(toMouse);

        // Magnet pull if within range
        if (dist < 80.f)
        {
            sf::Vector2f pull = normaliseVector(toMouse) * 150.f;
            it->velocity = pull;
        }

        it->shape.move(it->velocity * deltaTime);
        it->velocity *= .99f;

        // Despawn if close to mouse
        if (dist < 10.f)
        {   
            if (it->sourceSheep)
            {
                int value = econ.woolSellPrice + it->sourceSheep->myStats.woolBonus;
                woolCollectFunc(mousePos, value);
            }
            it = woolParticles.erase(it);
        }
        else
        {
            ++it;
        }
    }

	// Update floating texts for the cash earned when wool picked up
    for (auto it = floatingTexts.begin(); it != floatingTexts.end(); )
    {
        it->lifetime -= deltaTime;

        sf::Color color = it->text.getFillColor();
        color.a = static_cast<sf::Uint8>(std::max(0.f, color.a - it->fadeSpeed * deltaTime));
        it->text.setFillColor(color);

        it->text.move(it->velocity * deltaTime);

        if (it->lifetime <= 0 || color.a <= 0) // If life over if completely faded, kill
            it = floatingTexts.erase(it);
        else
            ++it;
    }

    if (sheepHeartCooldown > 0.f)
    {
        sheepHeartCooldown -= deltaTime;
    }

    dog.Update(mousePos);

    if (econ.combine)
    {
        combineFunc(sheepArray);
    }

    herd.clear();
    for (auto& sheep : sheepArray)
    {
        herd.push_back(&sheep);
    }

    if (wolf && wolf->isDead())
    {
        particleSpawner.emitFunc(wolf->getPosition(), ParticleType::WolfDying);
        wolf.reset();
        wolvesAbout = 0; // Mark Wolf is gone
    }

} // End of Update

// Gives the player his money for picking up wool, then spawns floating text
void World::woolCollectFunc(sf::Vector2i mousePos, int value)
{ 
   econ.addFunds(value);

   FloatingText newText;  
   newText.text.setFont(Font);  
   newText.text.setString("+" + std::to_string(value));
   newText.text.setCharacterSize(20);  
   newText.text.setFillColor(sf::Color(255, 255, 255, 255));  
   newText.text.setPosition(mousePos.x, mousePos.y - 15);  
   newText.velocity = sf::Vector2f(0.f, -30.f);  
   floatingTexts.push_back(newText);  
}

void World::combineFunc(std::vector< Sheep>& sheepArray)
{
    // Count sheep that *can* reproduce
    int reproSheepCount = std::count_if(sheepArray.begin(), sheepArray.end(),
        [](const Sheep& s) { return s.myStats.canReproduce; });

    if (reproSheepCount < 30)
    {
        econ.combine = false;
        return;
    }
    else {
        sf::Vector2f target = { 600.f, 855.f };
        bool allAtTarget = true;

        for (Sheep& sheep : sheepArray)
        {
            if (!sheep.isArrived)
            {
                sf::Vector2f pos = sheep.getPosition();
                sf::Vector2f newPos = lerp(pos, target, 0.05f);
                sheep.setPosition(newPos);

                if (getDistanceBetween(newPos, target) > 20.f)
                    allAtTarget = false;
                else
                    sheep.isArrived = true;
            }

            if (!sheep.isArrived)
                allAtTarget = false;
        }

        if (allAtTarget)
        {
            std::vector<Sheep*> reproSheep;
            for (Sheep& sheep : sheepArray)
            {
                if (sheep.myStats.canReproduce)
                    reproSheep.push_back(&sheep);
            }

            // Sorts the array so the greatess sheep is first
            std::sort(reproSheep.begin(), reproSheep.end(), [](const Sheep* a, const Sheep* b) {
                return a->getGreatness() > b->getGreatness();
                });

            // Take top 4
            std::vector<Sheep> top4;
            for (int i = 0; i < 4; ++i)
            {
                top4.push_back(*reproSheep[i]);
            }

            combiner.Combine(top4, sheepArray);

            // Remove the sheep that got combined
            for (int i = 0; i < 30; ++i)
            {
                Sheep* toRemove = reproSheep[i];
                auto it = std::find_if(sheepArray.begin(), sheepArray.end(), [&](const Sheep& s) {
                    return &s == toRemove;
                    });

                if (it != sheepArray.end())
                {
                    sheepArray.erase(it);
                }
            }

            econ.combine = false;
        }
    }
}

// Displays the cost of the upgrade when hovering over the button so player can see prices
void World::displayCosts(sf::Vector2i mousePos)
{
	// Holds the text to be displayed
    struct UpgradeButtonData {
        sf::Sprite& sprite;
        std::string key;
    };

	// List of upgrade buttons and their corresponding keys got from Economy
    std::vector<UpgradeButtonData> upgradeButtons = {
        { econ.hud.getUpgradeButton_MaxSheep(), "up_MaxSheep" },
        { econ.hud.getUpgradeButton_WoolSell(), "up_WoolSell" },
        { econ.hud.getUpgradeButton_SheepAmount(), "up_MoreSheep" },
        { econ.hud.getUpgradeButton_BetterGrass(), "up_MoreGrass" }
    };

    // The upgrades
    for (const auto& upgrade : upgradeButtons)
    {
        sf::FloatRect bounds = upgrade.sprite.getGlobalBounds(); // Hitbox

        if (bounds.contains(static_cast<sf::Vector2f>(mousePos)))
        {
			// Get the price from the map
            auto& map = econ.upgradeMap[upgrade.key];

			// If the map is not empty, get the first price which is the costs
            if (!map.empty())
            {
                float price = map.begin()->first;

                upgradeText.setString("$" + std::to_string(static_cast<int>(price)));
                upgradeText.setPosition(static_cast<sf::Vector2f>(mousePos) + sf::Vector2f(20.f, 10.f));
                showHoverText = true;
                break;
            }
        }
        else {
			showHoverText = false; // If not hovering over any button, hide the text
        }
    }

    // The other purchases
	if (econ.hud.getBuyButton().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		upgradeText.setString("$" + std::to_string(econ.sheepBuyPrice));
		upgradeText.setPosition(static_cast<sf::Vector2f>(mousePos) + sf::Vector2f(20.f, 10.f));
		showHoverText = true;
	}
	else if (econ.hud.getGrassButton().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		upgradeText.setString("$" + std::to_string(econ.fertiliserPrice));
		upgradeText.setPosition(static_cast<sf::Vector2f>(mousePos) + sf::Vector2f(20.f, 10.f));
		showHoverText = true;
	}
    else if (econ.hud.getSellButton().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
        upgradeText.setString("$" + std::to_string(econ.sheepSellPrice));
        upgradeText.setPosition(static_cast<sf::Vector2f>(mousePos) + sf::Vector2f(20.f, 10.f));
        showHoverText = true;
    }
}

void World::FixedUpdate(sf::Vector2i mousePos)
{
    bg.setFillColor(DaylightCycle());
    updateFencedGrass();
    WorldTime();
    econ.update(mousePos);
}

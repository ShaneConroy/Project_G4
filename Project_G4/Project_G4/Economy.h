#pragma once
#include "Global.h"
#include "Funds_Enum.h"
#include "Sheep.h"
#include "HUD.h"


class Economy
{
public:

	bool sheepPurchased = false;
	bool sheepSold = false;
	bool fertiliserPurchased = false;
	bool popOpen = false;
	bool up_MaxSheepBool = false;
	bool up_WoolSellPrice = false;
	bool up_SheepAmountBool = false;
	bool up_GrassAmountBool = false;
	bool stuck = false;
	bool whistle = false;

	void update();
	void addFunds(Funds_Enum fundType);
	void calculatePassiveIncome(int);

	void sellSheep(sf::Vector2i);
	void buySheep(sf::Vector2i);
	void buyGrass(sf::Vector2i);
	void popOutPanelFunc(sf::Vector2i);
	void upgradeMaxSheep(sf::Vector2i);
	void upgradeWoolPrice(sf::Vector2i);
	void upgradeSheepPurchaseAmount(sf::Vector2i);
	void upgradeGrassPurchaseAmount(sf::Vector2i);
	void stuckButtonFunc(sf::Vector2i);
	void whistleButtonFunc(sf::Vector2i);

	void upgradeBarn(sf::IntRect);
	void upgradeLoom(sf::IntRect);
	void upgradeMarket(sf::IntRect);
	void upgradeGarden(sf::IntRect);

	void setUpUpgradeMaps();

	int barnLevel = 0;
	int loomLevel = 0;
	int marketLevel = 0;
	int gardenLevel = 0;

	void draw(sf::RenderWindow&, bool);

	HUD hud;

private:

	Funds_Enum fundType;
	Sheep sheep;

	int currentFunds = 999999;

	int fertiliserPrice = 50;
	int sheepBuyPrice = 100;
	int sheepSellPrice = 50;

	int buttonDelay = 12;

	int buySheepDelay;
	int sellDelay;

	int passiveIncome;
	int passiveIncomeTimer;
	int passiveIncomeTimerCap = 60;

	int buyGrassDelay;
	int sellTimer;
	int buyTimer;
	int grassTimer;
	int popTimer;
	int up_MaxSheepTimer;
	int up_WoolPriceTimer;
	int up_SheepBuyAmountTimer;
	int up_GrassBuyAmountTimer;
	int stuckTimer;
	int whistleTimer;

	const int maxBarnLevel = 5; // Max sheep
	const int maxLooomLevel = 5; // Wool sell price
	const int maxMarketLevel = 5; // Sheep bought at a time
	const int maxGardenLevel = 5; // Grass bought at a time

	std::map<std::string, std::map<float, float>> upgradeMap;

	void applyUpgrade(std::map<float, float>&);
	void purchaseSheep();
	void purchaseGrass();

	int checkFunds();

};


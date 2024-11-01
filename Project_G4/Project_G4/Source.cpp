#ifdef _DEBUG  
#pragma comment(lib,"sfml-graphics-d.lib")  
#pragma comment(lib,"sfml-audio-d.lib")  
#pragma comment(lib,"sfml-system-d.lib")  
#pragma comment(lib,"sfml-window-d.lib")  
#pragma comment(lib,"sfml-network-d.lib")  
#else  
#pragma comment(lib,"sfml-graphics.lib")  
#pragma comment(lib,"sfml-audio.lib")  
#pragma comment(lib,"sfml-system.lib")  
#pragma comment(lib,"sfml-window.lib")  
#pragma comment(lib,"sfml-network.lib")  
#endif  

#include <iostream>
#include <SFML/Graphics.hpp> 

#include "World.h"
#include "Menu.h"

void main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML Project");

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;
	clock.restart();

	World world;
	Menu menu;

	bool gameRunning = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		timeSinceLastUpdate += clock.restart();


		//________________Update_____________//
		if (timeSinceLastUpdate > timePerFrame)
		{
			sf::Vector2i getMousePosition = { sf::Mouse::getPosition(window) };
			if (!gameRunning) // Not in game
			{
				menu.Draw(window);
				
				if (menu.StartButtonFunction(getMousePosition) == true)
				{
					gameRunning = true;
					menu.~Menu();
				}
			}
			else if (gameRunning) // In game
			{
				window.clear(world.DaylightCycle());
				world.Draw(window);
			}
			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		} // End of Update
	}
}
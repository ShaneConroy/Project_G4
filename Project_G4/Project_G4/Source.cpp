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
#include "Sheep.h"
#include "HUD.h"

void main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML Project");

    const sf::Time fixedTimeStep = sf::seconds(1.0f / 60.0f);
    sf::Time timeSinceLastFixedUpdate = sf::Time::Zero;
    sf::Clock clock;
    clock.restart();

    World world;
    Menu menu;
    Sheep sheep;
	HUD hud;

    bool gameRunning = false;

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        sf::Vector2i getMousePosition = { sf::Mouse::getPosition(window) };

        sf::Time deltaTime = clock.restart();
        timeSinceLastFixedUpdate += deltaTime;

        //____________________________Update__________________________________//
        if (!gameRunning) // Not in game
        {
            window.clear();

            menu.Draw(window);

            if (menu.StartButtonFunction(getMousePosition) == true)
            {
                gameRunning = true;
                menu.~Menu();
            }
        }
        else if (gameRunning) // In game
        {
            world.Update(deltaTime.asSeconds(), getMousePosition);

            world.Draw(window);
        }
        
        window.display();

        //_________________________Fixed_Update_______________________________//
        if(gameRunning)
        {
            while (timeSinceLastFixedUpdate >= fixedTimeStep)
            {
                window.setFramerateLimit(60);
                world.FixedUpdate();

                timeSinceLastFixedUpdate -= fixedTimeStep;
            }
        }
    }
}

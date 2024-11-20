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

void main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML Project");

    const sf::Time fixedTimeStep = sf::seconds(1.0f / 60.0f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timeSinceLastFixedUpdate = sf::Time::Zero;
    sf::Clock clock;
    clock.restart();

    World world;
    Menu menu;
    Sheep sheep;

    bool gameRunning = false;

    sf::Text fps;
    sf::Font BebasNeue;
    if (!BebasNeue.loadFromFile("ASSETS/FONT/BebasNeue.otf"))
        std::cout << "Font failed to load!" << "\n";
    fps.setFont(BebasNeue);
    fps.setCharacterSize(20);

    int frameCount = 0;
    float elapsedTime = 0.0f;

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        sf::Vector2i getMousePosition = { sf::Mouse::getPosition(window) };

        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;
        timeSinceLastFixedUpdate += deltaTime;

        ////Checking framerate
        //frameCount++;
        //elapsedTime += deltaTime.asSeconds();
        //if (elapsedTime >= 1.0f)
        //{
        //    fps.setString(std::to_string(frameCount));
        //    frameCount = 0;
        //    elapsedTime = 0.f;
        //}

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
            world.Update(deltaTime.asSeconds());
            
            world.Draw(window);

            //window.draw(fps);
        }
        
        window.display();

        //_________________________Fixed_Update_______________________________//
        if(gameRunning)
        {
            while (timeSinceLastFixedUpdate >= fixedTimeStep)
            {
                world.FixedUpdate();
                
                timeSinceLastFixedUpdate -= fixedTimeStep;
            }
        }
    }
}

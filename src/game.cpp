#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "constants.hpp"
#include "player.hpp"
#include "entity.hpp"
#include <algorithm>

// Define global entities vector
std::vector<std::unique_ptr<Entity>> entities;

Game::Game()
{
}

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}), Constants::WINDOW_TITLE);
    window.setFramerateLimit(Constants::FRAMERATE_LIMIT);
    sf::Clock clock;
    
    entities.push_back(std::make_unique<Player>());
    
    // run the program as long as the window is open
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);
        toAddList.clear();
        for (size_t i = 0; i < entities.size(); ++i)
        {
            entities[i]->update(deltaTime);
            entities[i]->render(window);
        }

        for(auto& entity : toAddList)
        {
            entities.push_back(std::move(entity));
        }
        
        // Remove dead entities
        entities.erase(
            std::remove_if(entities.begin(), entities.end(),
                [](const std::unique_ptr<Entity>& e) { return e->isDead; }),
            entities.end()
        );

        window.display();
    }
}

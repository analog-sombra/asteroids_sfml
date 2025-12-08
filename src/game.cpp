#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "constants.hpp"
#include "player.hpp"
#include "entity.hpp"
#include <algorithm>
#include <list>
#include "asteroid.hpp"

// Define static member variables
std::vector<std::unique_ptr<Entity>> Game::entities;
std::list<std::unique_ptr<Entity>> Game::toAddList;

Game::Game()
{
}

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}), Constants::WINDOW_TITLE);
    window.setFramerateLimit(Constants::FRAMERATE_LIMIT);
    sf::Clock clock;

    Game::entities.push_back(std::make_unique<Player>());
    // Game::entities.push_back(std::make_unique<Asteroid>(sf::Vector2f(1, 0)));

    float asteroidSpawnTimer = Constants::ASTEROID_SPAWN_TIME;

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

        Game::toAddList.clear();

        window.clear(sf::Color::Black);

        asteroidSpawnTimer -= deltaTime;

        for (size_t i = 0; i < Game::entities.size(); ++i)
        {
            Game::entities[i]->update(deltaTime);
            Game::entities[i]->render(window);
        }

        for (auto &entity : Game::toAddList)
        {
            Game::entities.push_back(std::move(entity));
        }

        // Remove dead entities
        std::erase_if(Game::entities, [](const auto &e)
                      { return e->isDead; });

        if (asteroidSpawnTimer <= 0.f)
        {
            Game::entities.push_back(std::make_unique<Asteroid>(Asteroid::getRandomDirection(), Asteroid::getRandomPosition()));
            asteroidSpawnTimer = Constants::ASTEROID_SPAWN_TIME;
        }

        window.display();
    }
}

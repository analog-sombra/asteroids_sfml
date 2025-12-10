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
size_t Game::score{};
float Game::asteroidSpawnTimer{};
std::optional<sf::Text> Game::scoreText;
sf::Font Game::font;
std::unordered_map<std::string, sf::SoundBuffer> Game::soundBuffers;

Game::Game()
{
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        // Handle error - font failed to load
    }
    
    // Load sound buffers BEFORE creating entities
    if (!soundBuffers["shoot"].loadFromFile("../../assets/sounds/shoot.mp3")) {
        // Handle error - sound failed to load
    }
    
    scoreText.emplace(font);
    scoreText->setFillColor(sf::Color::White);
    scoreText->setPosition({10.f, 10.f});
    scoreText->setCharacterSize(24);
    Game::entities.push_back(std::make_unique<Player>());
    asteroidSpawnTimer = Constants::ASTEROID_SPAWN_TIME;
}

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}), Constants::WINDOW_TITLE);
    window.setFramerateLimit(Constants::FRAMERATE_LIMIT);
    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen())
    {

        handelEvents(window);

        float deltaTime = clock.restart().asSeconds();

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
            Game::entities.push_back(std::make_unique<Asteroid>());
            asteroidSpawnTimer = Constants::ASTEROID_SPAWN_TIME;
        }

        scoreText->setString("Score: " + std::to_string(score));
        window.draw(*scoreText);
        window.display();
    }
}

void Game::handelEvents(sf::RenderWindow &window)
{
    // check all the window's events that were triggered since the last iteration of the loop
    while (const std::optional event = window.pollEvent())
    {
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>())
            window.close();
    }
    // Placeholder for event handling logic
}
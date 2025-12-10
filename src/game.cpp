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
std::optional<sf::Text> Game::gameOverText;
std::optional<sf::Text> Game::continueText;
std::optional<sf::Text> Game::menuText;
std::optional<sf::Text> Game::playText;
std::optional<sf::Text> Game::exitText;
std::optional<sf::Text> Game::gotoMenuText;
sf::Font Game::font;
sf::SoundBuffer Game::shootSoundBuffer;
std::optional<sf::Sound> Game::shootSound;
Game::State Game::state = Game::MENU;

Game::Game()
{
}

void Game::init()
{
    if (!font.openFromFile("assets/fonts/arial.ttf"))
    {
        // Handle error - font failed to load
    }

    // Load sound buffers BEFORE creating entities
    if (!shootSoundBuffer.loadFromFile("assets/sounds/shoot.mp3"))
    {
        // Handle error - sound failed to load
    }
    shootSound.emplace(shootSoundBuffer);

    scoreText.emplace(font);
    scoreText->setFillColor(sf::Color::White);
    scoreText->setPosition({10.f, 10.f});
    scoreText->setCharacterSize(24);

    gameOverText.emplace(font, "Game Over!", 48);
    gameOverText->setFillColor(sf::Color::Red);
    auto bounds = gameOverText->getLocalBounds();
    gameOverText->setPosition({Constants::WINDOW_WIDTH / 2.f - bounds.size.x / 2.f,
                               Constants::WINDOW_HEIGHT / 2.f - bounds.size.y / 2.f});
    gameOverText->setCharacterSize(48);

    continueText.emplace(font, "Press Enter to Restart", 24);
    continueText->setFillColor(sf::Color::White);
    auto contBounds = continueText->getLocalBounds();
    continueText->setPosition({Constants::WINDOW_WIDTH / 2.f - contBounds.size.x / 2.f,
                               Constants::WINDOW_HEIGHT / 2.f + bounds.size.y});
    continueText->setCharacterSize(24);

    menuText.emplace(font, "Asteroids Game", 48);
    menuText->setFillColor(sf::Color::Cyan);
    auto menuBounds = menuText->getLocalBounds();
    menuText->setPosition({Constants::WINDOW_WIDTH / 2.f - menuBounds.size.x / 2.f,
                           Constants::WINDOW_HEIGHT / 2.f - menuBounds.size.y / 2.f - 50.f});
    menuText->setCharacterSize(48);

    playText.emplace(font, "Press Enter to Play", 24);
    playText->setFillColor(sf::Color::White);
    auto playBounds = playText->getLocalBounds();
    playText->setPosition({Constants::WINDOW_WIDTH / 2.f - playBounds.size.x / 2.f,
                           Constants::WINDOW_HEIGHT / 2.f + menuBounds.size.y / 2.f});
    playText->setCharacterSize(24);

    gotoMenuText.emplace(font, "Press Esc to go to Menu", 24);
    gotoMenuText->setFillColor(sf::Color::White);
    auto gotoMenuBounds = gotoMenuText->getLocalBounds();
    gotoMenuText->setPosition({10.f, Constants::WINDOW_HEIGHT - gotoMenuBounds.size.y - 10.f});
    gotoMenuText->setCharacterSize(24);

    exitText.emplace(font, "Press Esc to Exit", 24);
    exitText->setFillColor(sf::Color::White);
    auto exitBounds = exitText->getLocalBounds();
    exitText->setPosition({Constants::WINDOW_WIDTH / 2.f - exitBounds.size.x / 2.f,
                           Constants::WINDOW_HEIGHT / 2.f + menuBounds.size.y / 2.f + 40.f});
    exitText->setCharacterSize(24);

    state = MENU;
}

void Game::begin()
{
    state = PLAYING;
    Game::entities.push_back(std::make_unique<Player>());
    asteroidSpawnTimer = Constants::ASTEROID_SPAWN_TIME;
    score = 0;
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

        window.clear(sf::Color::Black);

        

        if (state == MENU)
        {
            window.draw(*menuText);
            window.draw(*playText);
            window.draw(*exitText);
            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
            {
                begin();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                window.close();
            }
            continue;
        }

       

        Game::toAddList.clear();
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

        if (state == GAMEOVER)
        {
            entities.clear();
            window.draw(*gameOverText);
            window.draw(*continueText);
            window.draw(*gotoMenuText);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
            {
                score = 0;
                begin();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                state = MENU;
            }
        }
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

void Game::gameOver()
{
    state = GAMEOVER;
}
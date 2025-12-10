#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <vector>
#include <memory>
#include <list>
#include <optional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>

class Entity;

class Game
{
public:
    Game();
    void run();
    static void init();
    static void begin();
    void handelEvents(sf::RenderWindow &window);
    static void gameOver();
    static std::list<std::unique_ptr<Entity>> toAddList;
    static std::vector<std::unique_ptr<Entity>> entities;
    static size_t score;
    static size_t highScore;
    static size_t health;
    static sf::SoundBuffer shootSoundBuffer;
    static std::optional<sf::Sound> shootSound;

private:
    static float asteroidSpawnTimer;
    static sf::Font font;
    static std::optional<sf::Text> scoreText;
    static std::optional<sf::Text> gameOverText;
    static std::optional<sf::Text> continueText;
    static std::optional<sf::Text> menuText;
    static std::optional<sf::Text> playText;
    static std::optional<sf::Text> exitText;
    static std::optional<sf::Text> gotoMenuText;

    static enum State { MENU,
                        PLAYING,
                        GAMEOVER } state;
};

#endif // __GAME_HPP__
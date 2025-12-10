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
    void handelEvents(sf::RenderWindow &window);

    static std::list<std::unique_ptr<Entity>> toAddList;
    static std::vector<std::unique_ptr<Entity>> entities;
    static size_t score;
    static size_t highScore;
    static size_t health;
    static std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;

private:
    static float asteroidSpawnTimer;
    static sf::Font font;
    static std::optional<sf::Text> scoreText;
};

#endif // __GAME_HPP__
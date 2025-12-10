#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__
#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include <SFML/Audio.hpp>
#include <optional>


class Player : public Entity
{
public:
    Player();
    void render(sf::RenderWindow &window) override;
    void update(float deltaTime) override;

private:
    sf::VertexArray shape;
    std::optional<sf::Sound> shootSound;
    float shootTimer;
};

#endif // __PLAYER_HPP__
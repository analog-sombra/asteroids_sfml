#ifndef __BULLET_HPP__
#define __BULLET_HPP__

#include <SFML/Graphics.hpp>
#include "entity.hpp"

class Bullet : public Entity
{
public:
    Bullet(const sf::Vector2f& position, const sf::Vector2f& direction);
    void render(sf::RenderWindow &window) override;
    void update(float deltaTime) override;

private:
    sf::Vector2f direction;
    sf::CircleShape shape;
    float lifetime;
};

#endif // __BULLET_HPP__
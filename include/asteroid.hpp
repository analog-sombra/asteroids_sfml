#ifndef __ASTEROID_HPP__
#define __ASTEROID_HPP__
#include <SFML/Graphics.hpp>
#include "entity.hpp"

class Asteroid : public Entity
{
public:
    Asteroid(
        sf::Vector2f direction = Asteroid::getRandomDirection(),
        sf::Vector2f position = Asteroid::getRandomPosition());
    void render(sf::RenderWindow &window) override;
    void update(float deltaTime) override;
    const sf::VertexArray& getVertexArray() const;

    static sf::Vector2f getRandomDirection();
    static sf::Vector2f getRandomPosition();


private:
    sf::VertexArray shape;
    sf::Vector2f direction;
};

#endif // __ASTEROID_HPP__
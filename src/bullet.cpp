#include "bullet.hpp"
#include "constants.hpp"
#include <SFML/Graphics/Transform.hpp>
#include "game.hpp"
#include "asteroid.hpp"
#include "physics.hpp"

Bullet::Bullet(const sf::Vector2f &position, const sf::Vector2f &direction)
    : Entity(position, 0.f), shape(1.0f), direction(direction), lifetime(Constants::BULLET_LIFETIME)
{
    shape.setFillColor(sf::Color::White);
}

void Bullet::update(float deltaTime)
{
    position += direction * Constants::BULLET_SPEED * deltaTime;

    lifetime -= deltaTime;
    if (lifetime <= 0)
    {
        isDead = true;
    }
    // if goes out of bounds, mark as dead
    if (position.x < 0 || position.x > Constants::WINDOW_WIDTH ||
        position.y < 0 || position.y > Constants::WINDOW_HEIGHT)
    {
        isDead = true;
    }

    for (size_t i = 0; i < Game::entities.size(); ++i)
    {
        if (typeid(*Game::entities[i]) == typeid(Asteroid))
        {
            Asteroid *asteroid = dynamic_cast<Asteroid *>(Game::entities[i].get());
            sf::Transform transform = sf::Transform().translate(asteroid->position).rotate(sf::degrees(asteroid->angle));

            if (physics::intersects(position, physics::getTransformedPolygon(asteroid->getVertexArray(), transform)))
            {
                isDead = true;
                asteroid->isDead = true;
                Game::score += 10;
                break;
            }
        }
    }
}

void Bullet::render(sf::RenderWindow &window)
{
    window.draw(shape, sf::Transform().translate(position));
}
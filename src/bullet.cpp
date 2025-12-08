#include "bullet.hpp"
#include "constants.hpp"
#include <SFML/Graphics/Transform.hpp>

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
}

void Bullet::render(sf::RenderWindow &window)
{
    window.draw(shape, sf::Transform().translate(position));
}
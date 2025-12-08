#include "asteroid.hpp"
#include "constants.hpp"
#include <numbers>
#include "bullet.hpp"
#include "game.hpp"
#include <random>
#include <cmath>

Asteroid::Asteroid(sf::Vector2f direction, sf::Vector2f position)
    : Entity(position, 0), shape(sf::PrimitiveType::LineStrip, 12),
      direction(direction)
{
    shape[0].position = sf::Vector2f(-40, 40);
    shape[1].position = sf::Vector2f(-50, 10);
    shape[2].position = sf::Vector2f(-10, -20);
    shape[3].position = sf::Vector2f(-20, -40);
    shape[4].position = sf::Vector2f(10, -40);
    shape[5].position = sf::Vector2f(40, -20);
    shape[6].position = sf::Vector2f(40, -10);
    shape[7].position = sf::Vector2f(10, 0);
    shape[8].position = sf::Vector2f(40, 20);
    shape[9].position = sf::Vector2f(20, 40);
    shape[10].position = sf::Vector2f(0, 30);
    shape[11].position = shape[0].position; // Close the loop

    for (size_t i = 0; i < shape.getVertexCount(); ++i)
    {
        shape[i].color = sf::Color::White;
    }
}

void Asteroid::render(sf::RenderWindow &window)
{
    sf::Transform transform;
    transform.translate(position);
    transform.rotate(sf::degrees(angle));

    window.draw(shape, transform);
}

void Asteroid::update(float deltaTime)
{
    position += direction * Constants::ASTEROID_SPEED * deltaTime;
    angle += Constants::ASTEROID_SPIN * deltaTime;
}

sf::Vector2f Asteroid::getRandomDirection()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 2.0f * std::numbers::pi);

    float angle = dist(gen);
    return sf::Vector2f(std::cos(angle), std::sin(angle));
}

sf::Vector2f Asteroid::getRandomPosition()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.0f, static_cast<float>(Constants::WINDOW_WIDTH));
    std::uniform_real_distribution<float> distY(0.0f, static_cast<float>(Constants::WINDOW_HEIGHT));

    return sf::Vector2f(distX(gen), distY(gen));
}
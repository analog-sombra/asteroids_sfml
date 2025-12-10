#include "player.hpp"
#include "constants.hpp"
#include <numbers>
#include "bullet.hpp"
#include "game.hpp"
#include "physics.hpp"
#include "asteroid.hpp"

Player::Player()
    : Entity(sf::Vector2f(500, 500), 0), shape(sf::PrimitiveType::LineStrip, 5),
      shootTimer(0.f)
{
    shape[0].position = sf::Vector2f(20.f, 0.f);
    shape[1].position = sf::Vector2f(-30.f, -20.f);
    shape[2].position = sf::Vector2f(-15.f, 0.f);
    shape[3].position = sf::Vector2f(-30.f, 20.f);
    shape[4].position = shape[0].position; // Close the loop

    for (size_t i = 0; i < shape.getVertexCount(); ++i)
    {
        shape[i].color = sf::Color::White;
    }
}

void Player::render(sf::RenderWindow &window)
{
    sf::Transform transform;
    transform.translate(position);
    transform.rotate(sf::degrees(angle));

    window.draw(shape, transform);
}

void Player::update(float deltaTime)
{
    shootTimer -= deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        angle -= Constants::TURN_SPEED * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        angle += Constants::TURN_SPEED * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        float radians = angle * (std::numbers::pi / 180.0f);
        position.x += cos(radians) * Constants::PLAYER_SPEED * deltaTime;
        position.y += sin(radians) * Constants::PLAYER_SPEED * deltaTime;
    }
    position.x = std::min(std::max(position.x, Constants::PLAYER_WIDTH / 2), static_cast<float>(Constants::WINDOW_WIDTH) - Constants::PLAYER_WIDTH / 2);
    position.y = std::min(std::max(position.y, Constants::PLAYER_HEIGHT / 2), static_cast<float>(Constants::WINDOW_HEIGHT) - Constants::PLAYER_HEIGHT / 2);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && shootTimer <= 0.f)
    {
        if (Game::shootSound.has_value())
            Game::shootSound->play();
        shootTimer = Constants::SHOOT_COOLDOWN;
        float radians = angle * (std::numbers::pi / 180.0f);
        // Calculate bullet spawn position at the front of the ship
        sf::Vector2f bulletPos = position + sf::Vector2f(cos(radians) * 20.f, sin(radians) * 20.f);
        // Fire bullet
        Game::toAddList.push_back(std::make_unique<Bullet>(bulletPos, sf::Vector2f(cos(radians), sin(radians))));
    }

    sf::Transform playerTransform = sf::Transform().translate(position).rotate(sf::degrees(angle));
    for (size_t i = 0; i < Game::entities.size(); ++i)
    {
        if (typeid(*Game::entities[i]) == typeid(Asteroid))
        {
            Asteroid *asteroid = dynamic_cast<Asteroid *>(Game::entities[i].get());

            if (asteroid->getLife() < Constants::ASTEROID_HIT_TIME)
            {
                continue;
            }
            sf::Transform asteroidTransform = sf::Transform().translate(asteroid->position).rotate(sf::degrees(asteroid->angle));

            if (physics::intersects(physics::getTransformedPolygon(shape, playerTransform), physics::getTransformedPolygon(asteroid->getVertexArray(), asteroidTransform)))
            {
                Game::gameOver();
                break;
            }
        }
    }
}

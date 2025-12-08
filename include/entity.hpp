#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Entity
{
public:
    Entity(sf::Vector2f position, float angle)
        : position(position), angle(angle), isDead(false) {}
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow &window) = 0;

    sf::Vector2f position;
    float angle;
    bool isDead;
};

// Global entities vector
extern std::vector<std::unique_ptr<Entity>> entities;
extern std::list<std::unique_ptr<Entity>> toAddList;

#endif // __ENTITY_HPP__
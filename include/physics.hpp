#ifndef __PHYSICS_HPP__
#define __PHYSICS_HPP__

#include <SFML/Graphics.hpp>
namespace physics
{
    bool intersects(sf::Vector2f point, const sf::VertexArray &polygon);
    sf::VertexArray getTransformedPolygon(const sf::VertexArray &polygon, const sf::Transform &transform);

} // namespace physics

#endif // __PHYSICS_HPP__
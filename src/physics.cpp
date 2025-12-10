#include "physics.hpp"
#include <SFML/Graphics/Transform.hpp>

namespace physics
{
    bool intersects(sf::Vector2f point, const sf::VertexArray &polygon)
    {
        size_t n = polygon.getVertexCount() - 1; // Last vertex is same as first
        size_t intersectionCount = 0;
        sf::Vector2 rayEnd = sf::Vector2(std::numeric_limits<float>::max(), point.y);

        for (size_t i = 0; i < n; i++)
        {
            sf::Vector2 p1 = polygon[i].position;
            sf::Vector2 p2 = polygon[(i + 1) % n].position;

            if ((p1.y < point.y && p2.y >= point.y) || (p2.y < point.y && p1.y >= point.y))
            {
                float t = (point.y - p1.y) / (p2.y - p1.y);
                float interrsectX = p1.x + t * (p2.x - p1.x);

                if (interrsectX <= point.x && interrsectX <= rayEnd.x)
                {
                    intersectionCount++;
                }
            }
        }

        return intersectionCount % 2 == 1;
    }

    sf::VertexArray getTransformedPolygon(const sf::VertexArray &polygon, const sf::Transform &transform)
    {
        sf::VertexArray transformed = polygon;

        for (size_t i = 0; i < transformed.getVertexCount(); ++i)
        {
            transformed[i].position = transform.transformPoint(transformed[i].position);
        }

        return transformed;
    }
}

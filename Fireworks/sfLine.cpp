#include "pch.h"
#include "sfLine.h"


sfLine::sfLine(const sf::Vector2f& point1, const sf::Vector2f& point2, sf::Color color, float thickness)
  : color_(color), thickness_(thickness)
{
  sf::Vector2f direction = point2 - point1;
  sf::Vector2f unitDirection = direction / std::sqrt(direction.x*direction.x + direction.y*direction.y);
  sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

  sf::Vector2f offset = (thickness_ / 2.f)*unitPerpendicular;

  vertices_[0].position = point1 + offset;
  vertices_[1].position = point2 + offset;
  vertices_[2].position = point2 - offset;
  vertices_[3].position = point1 - offset;

  for (int i = 0; i < 4; ++i)
    vertices_[i].color = color_;
}

void sfLine::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(vertices_, 4, sf::Quads);
}
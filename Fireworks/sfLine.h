#pragma once
#include <SFML\Graphics.hpp>

// https://github.com/SFML/SFML/wiki/Source:-Line-segment-with-thickness

class sfLine : public sf::Drawable
{
public:
  sfLine(const sf::Vector2f& point1, const sf::Vector2f& point2, sf::Color color, float thickness = 1);
  void draw(sf::RenderTarget & target, sf::RenderStates states) const;


private:
  sf::Vertex vertices_[4];
  float thickness_;
  sf::Color color_;
};






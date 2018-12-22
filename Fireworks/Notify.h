#pragma once
#include <SFML/Graphics.hpp>

class Notify
{
public:
  Notify();
  virtual ~Notify();

  virtual void notify(sf::Color color, sf::Time duration) = 0;
};


#pragma once
#include <SFML\Graphics.hpp>
#include "Notify.h"

class ManLight : public sf::Drawable, public Notify
{
public:
  ManLight(sf::Sprite &spriteManLight, sf::Sprite &spriteManDark);
  ~ManLight();

  void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
  void update();

  void setColor(sf::Color color);
  sf::Color getColor();

  virtual void notify(sf::Color color, sf::Time duration);

private:
  bool       fired = false;
  sf::Color  color_;
  sf::Sprite &spriteManLight_;
  sf::Sprite &spriteManDark_;
  sf::Clock  timer_;
  sf::Time   fireDuration_;
};

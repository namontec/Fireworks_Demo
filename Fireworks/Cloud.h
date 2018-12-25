#pragma once
#include "Object.h"
#include <SFML\Graphics.hpp>

class Cloud : public Object
{
public:
                            Cloud(sf::RenderWindow &window, float x, float y);
                            ~Cloud();

  virtual void              update(float deltaTime);
  void                      draw(sf::RenderTarget & target, sf::RenderStates states) const override;
  virtual void              setPosition(sf::Vector2f position) override;

  Object::offscreenPosition checkOffscreenPosition(sf::Vector2f positon) override;

public:
  sf::Sprite sprite;

private:
  sf::RenderWindow window_;

};


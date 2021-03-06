#pragma once
#include "Object.h"
#include <SFML\Graphics.hpp>
#include <list>
#include <utility>

class Firework : public Object
{
public:
                      Firework(sf::RenderWindow &window, float x, float y, sf::Color color = sf::Color::White, sf::Time timeToLive = sf::Time::Zero);
  virtual             ~Firework();

  void                draw(sf::RenderTarget & target, sf::RenderStates states) const override;
  virtual void        update(float deltaTime) override;
  virtual void        setPosition(sf::Vector2f newPosition) override;
  virtual void        setColor(sf::Color color);
  virtual sf::Color   getColor() const;


  void addTrail(sf::Vector2f position);
  
  std::list<sf::Vector2f> trails;
  int trailMaxLenght         = 15;
  sf::Time trailMinTime      = sf::seconds(0.1f);
  sf::Time previousTrailTime = sf::Time::Zero;

  sf::CircleShape shape;

private:
  sf::Color color_;
  sf::Clock timer_;
  sf::Time  timeToLive_;

};


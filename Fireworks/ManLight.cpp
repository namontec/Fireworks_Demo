#include "pch.h"
#include "ManLight.h"




ManLight::ManLight(sf::Sprite &spriteManDark, sf::Sprite &spriteManLight)
  : spriteManDark_(spriteManDark), spriteManLight_(spriteManLight)
{
}

ManLight::~ManLight()
{
}

void ManLight::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(spriteManDark_);
  if (fired) { target.draw(spriteManLight_); }
}

void ManLight::update()
{
  sf::Time elapsed = timer_.getElapsedTime();

  bool fireworkIsFlying = elapsed < fireDuration_;
  if  (fireworkIsFlying) {
    float transparency =  255 - 255 * (float)elapsed.asSeconds() / (float)fireDuration_.asSeconds();
    setColor(sf::Color({ color_.r, color_.g, color_.b, (sf::Uint8)transparency }));
  }
  else { fired = false; }
}

void ManLight::setColor(sf::Color color)
{
  color_ = color;
  spriteManLight_.setColor(color);
}

sf::Color ManLight::getColor()
{
  return color_;
}

void ManLight::notify(sf::Color color, sf::Time duration)
{
  color_ = color;
  spriteManLight_.setColor(color_);
  fireDuration_ = duration;
  timer_.restart();
  fired = true;
}

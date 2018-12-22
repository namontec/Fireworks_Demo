#include "pch.h"
#include "Cloud.h"


Cloud::Cloud(sf::RenderWindow & window, float x, float y)
  : Object(window, x, y)
{
}

Cloud::~Cloud()
{
}


void Cloud::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(sprite);
}


void Cloud::setPosition(sf::Vector2f position)
{
  //check if cloud is outside main window
  Object::offscreenPosition result = checkOffscreenPosition(position);

  if (result != Object::offscreenPosition::Inside) {
    float windowWidth  = getWindow().getSize().x;
    float windowHeight = getWindow().getSize().y;
    float spriteWidth  = sprite.getGlobalBounds().width;
    float spriteHeight = sprite.getGlobalBounds().height;

    //if it is so, move it to the other side of the screen
    if (result == Object::offscreenPosition::BehindLeft)
      position.x = position.x + spriteWidth  + windowWidth;
    else if (result == Object::offscreenPosition::BehindRight)
      position.x = position.x - spriteWidth  - windowWidth;
    else if (result == Object::offscreenPosition::Above)
      position.y = position.y + spriteHeight + windowHeight;
    else if (result == Object::offscreenPosition::Below)
      position.y = position.y - spriteHeight - windowHeight;
  }

  Object::setPosition(position);
  sprite.setPosition(position);
}

Object::offscreenPosition Cloud::checkOffscreenPosition(sf::Vector2f position)
{
  float windowWidth  = getWindow().getSize().x;
  float windowHeight = getWindow().getSize().y;
  float spriteWidth  = sprite.getGlobalBounds().width;
  float spriteHeight = sprite.getGlobalBounds().height;
  
  bool isAbove       = (position.y + spriteHeight) < 0;
  bool isBelow       = position.y  > windowHeight;
  bool isBehindLeft  = (position.x + spriteWidth)  < 0;
  bool isBehindRight = position.x  > windowWidth;

  if      (isBehindLeft)  return Object::offscreenPosition::BehindLeft;
  else if (isBehindRight) return Object::offscreenPosition::BehindRight;
  else if (isAbove)       return Object::offscreenPosition::Above;
  else if (isBelow)       return Object::offscreenPosition::Below;
  else return Object::offscreenPosition::Inside;

}



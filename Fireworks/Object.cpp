#include "pch.h"
#include "Object.h"



Object::Object(sf::RenderWindow &window, float x, float y)
  : position_({ x, y }), window_(window)
{
}

Object::~Object()
{
}


void Object::update(float deltaTime)
{
  velocity_ += acceleration_ + gravity_;
  acceleration_ = { 0, 0 };

  setPosition (getPosition() + (velocity_ * deltaTime));
}

void Object::setPosition(sf::Vector2f position)
{
  position_ = position;
}

sf::Vector2f Object::getPosition() const
{
  return position_;
}

void Object::setAcceleration(sf::Vector2f acceleration)
{
  acceleration_ = acceleration;
}

void Object::setVelocity(sf::Vector2f velocity)
{
  velocity_ = velocity;
}

void Object::setGravity(sf::Vector2f gravity)
{
  gravity_ = gravity;
}


sf::RenderWindow& Object::getWindow() const
{
  return window_;
}


Object::offscreenPosition Object::checkOffscreenPosition(sf::Vector2f position)
{
  //!!!!
  return Object::offscreenPosition::Inside;
}

void Object::destroyObject()
{
  isDestroyed_ = true;
}

bool Object::isDestroyed() const
{
  return isDestroyed_;
}




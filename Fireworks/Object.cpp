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
  //if time has come - perfom fixedUpdate()
  timeSinceLastFixedUpate += sf::seconds(deltaTime);

  bool timeToFixedUpdate = timeSinceLastFixedUpate > fixedTimePerFrame;
  if (timeToFixedUpdate) {
    timeSinceLastFixedUpate -= fixedTimePerFrame;
    fixedUpdate(fixedTimePerFrame.asSeconds());
  }

  //regular update()
  velocity_ += acceleration_;
  acceleration_ = { 0, 0 };
  
  sf::Vector2f movement = velocity_ * deltaTime;
  setPosition( position_ + movement );
}

void Object::fixedUpdate(float fixedDeltaTime)
{
  velocity_ += gravity_;
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

sf::Vector2f Object::getAcceleration() const
{
  return acceleration_;
}

void Object::setVelocity(sf::Vector2f velocity)
{
  velocity_ = velocity;
}

sf::Vector2f Object::getVelocity() const
{
  return velocity_;
}

void Object::setGravity(sf::Vector2f gravity)
{
  gravity_ = gravity;
}

sf::Vector2f Object::getGravity() const
{
  return gravity_;
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




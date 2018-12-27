#pragma once

#include <SFML\Graphics.hpp>


class Object : public sf::Drawable
{
public:
                        Object(sf::RenderWindow &window, float x, float y);
  virtual               ~Object();

  virtual void          update      (float deltaTime);
  virtual void          fixedUpdate (float fixedDeltaTime);

  virtual void          setPosition(sf::Vector2f position);
  sf::Vector2f          getPosition() const;
  void                  setAcceleration(sf::Vector2f acceleration);
  sf::Vector2f          getAcceleration() const;
  void                  setVelocity(sf::Vector2f velocity);
  sf::Vector2f          getVelocity() const;
  void                  setGravity(sf::Vector2f gravity);
  sf::Vector2f          getGravity() const;


  sf::RenderWindow&     getWindow() const;

  enum class offscreenPosition { Inside, Above, Below, BehindLeft, BehindRight };
  virtual offscreenPosition checkOffscreenPosition(sf::Vector2f position);

  void                  destroyObject();
  bool                  isDestroyed() const;

private:
  sf::RenderWindow      &window_;
  bool                  isDestroyed_ = false;

  sf::Vector2f          position_           { 0, 0 };
  sf::Vector2f          acceleration_       { 0, 0 };
  sf::Vector2f          velocity_           { 0, 0 };
  sf::Vector2f          gravity_            { 0, 0 };
  sf::Vector2f          accumulatedGravity_ { 0, 0 };


  //FixedUpdate time variables
  const sf::Time        fixedTimePerFrame { sf::seconds(1.0f / 50.0f) };
  sf::Time              timeSinceLastFixedUpate  { sf::Time::Zero };
};


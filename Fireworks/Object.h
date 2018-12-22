#pragma once

#include <SFML\Graphics.hpp>


class Object : public sf::Drawable
{
public:
  Object(sf::RenderWindow &window, float x, float y);
  virtual ~Object();

  virtual void update(float deltaTime);

  virtual void setPosition(sf::Vector2f position);
  virtual sf::Vector2f getPosition() const;
  virtual void setAcceleration(sf::Vector2f acceleration);
  virtual void setVelocity(sf::Vector2f velocity);
  virtual void setGravity(sf::Vector2f gravity);


  void setWindow(sf::RenderWindow window);
  sf::RenderWindow& getWindow() const;

  enum class offscreenPosition { Inside, Above, Below, BehindLeft, BehindRight };
  virtual offscreenPosition checkOffscreenPosition(sf::Vector2f position);

  void destroyObject();
  bool isDestroyed() const;

private:
  sf::RenderWindow &window_;
  bool isDestroyed_ = false;

  sf::Vector2f position_     { 0, 0 };
  sf::Vector2f acceleration_ { 0, 0 };
  sf::Vector2f velocity_     { 0, 0 };
  sf::Vector2f gravity_      { 0, 0 };
};


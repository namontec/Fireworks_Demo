#pragma once
#include "Firework.h"
#include "Notify.h"
#include <list>

class FireworkStarter :
  public Firework
{
public:
                FireworkStarter(std::list<Object*> &objectPool, sf::RenderWindow &window, float x, float y, Notify *notify = nullptr);
  virtual       ~FireworkStarter();

  virtual void  update(float deltaTime) override;
  void          spawnFireworks();

  sf::Vector2f startPosition;
  sf::Vector2f spawnPosition;

private:
  std::list<Object*> &objectPool_;
  Notify *notify_;
};


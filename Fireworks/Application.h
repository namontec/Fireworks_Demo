#pragma once

#include <iostream>
#include <list>
#include <SFML\Graphics.hpp>

#include "Firework.h"
#include "FireworkStarter.h"
#include "Cloud.h"
#include "sprites.png.h"
#include "Man.h"


class Application
{
public:
  Application(int width, int height);
  ~Application();

  void run();

private:
  void init();
  void update(float deltaTime);
  void draw();



private:
  int mainWindowWidth_;
  int mainWindowHeight_;
  sf::RenderWindow window_;

  std::list<Object*>  objectPool;
  sf::Texture         texture;
  sf::Sprite          spriteBackground;
  sf::Sprite          spriteMan;
  sf::Sprite          spriteManLit;
  Man                 sittingMan(spriteMan, spriteManLit);
  Cloud*              clouds[4];

  //FixedUpdate time variables
  const sf::Time        fixedTimePerFrame{ sf::seconds(1.0f / 50.0f) };
  sf::Time              timeSinceLastFixedUpate{ sf::Time::Zero };
};


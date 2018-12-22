// Fireworks.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <list>
#include <SFML\Graphics.hpp>

#include "Firework.h"
#include "FireworkStarter.h"
#include "Cloud.h"
#include "sprites.png.h"


const int mainWindowWidth{ 1200 };
const int mainWindowHeight{ 800 };


std::list<Object*> objectPool;
sf::Texture texture;
sf::Sprite spriteBackground;
sf::Sprite spriteMan;
Cloud *clouds[4];



void init(sf::RenderWindow &window)
{
  //if (!texture.loadFromFile("png\\sprites2x.png"))
  //  std::cout << "error reading texture" << std::endl;

  texture.loadFromMemory(spritesData, sizeof(spritesData));

  spriteBackground.setTexture(texture);
  spriteBackground.setTextureRect(sf::IntRect(0, 536, 1200, 800));

  spriteMan.setTexture(texture);
  spriteMan.setTextureRect(sf::IntRect(0, 439, 1200, 96));
  spriteMan.setOrigin(0, 96);
  spriteMan.setPosition(0, mainWindowHeight);

  clouds[0] = new Cloud(window, -1400, -50);
  clouds[0]->sprite.setTexture(texture);
  clouds[0]->sprite.setTextureRect(sf::IntRect(0, 0, 1844, 438));
  clouds[0]->setAcceleration({ 20, 0 });

  clouds[1] = new Cloud(window, -800, 50);
  clouds[1]->sprite.setTexture(texture);
  clouds[1]->sprite.setTextureRect(sf::IntRect(0, 0, 1844, 438));
  clouds[1]->setAcceleration({ 20, 0 });
  clouds[1]->sprite.setColor(sf::Color(255, 255, 255, 50));

  clouds[2] = new Cloud(window, 600, 300);
  clouds[2]->sprite.setTexture(texture);
  clouds[2]->sprite.setTextureRect(sf::IntRect(0, 1337, 1004, 232));
  clouds[2]->setAcceleration({ 10, 0 });

  clouds[3] = new Cloud(window, -300, 400);
  clouds[3]->sprite.setTexture(texture);
  clouds[3]->sprite.setTextureRect(sf::IntRect(0, 1337, 1004, 232));
  clouds[3]->setAcceleration({ 10, 0 });
  clouds[3]->sprite.setColor(sf::Color(255, 255, 255, 50));

  objectPool.push_back(clouds[1]);
  objectPool.push_back(clouds[3]);
  objectPool.push_back(clouds[2]);
  objectPool.push_back(clouds[0]);

}


void draw(sf::RenderWindow &window)
{
  if (!objectPool.empty())
  {
    for (auto object : objectPool) {
      window.draw(*object);
    }
  }
}


void update(float deltaTime)
{
  if (!objectPool.empty())
  {
    for (auto p = objectPool.begin(); p != objectPool.end(); p++)
    {
      (*p)->update(deltaTime);

      bool objectIsDestroyed = (*p)->isDestroyed();
      if (objectIsDestroyed) {
        delete (*p);
        p = objectPool.erase(p);

        bool pIsEndIterator = ( p == objectPool.end() );
        if (pIsEndIterator) break;
      }
    }
  }
}



int main()
{
  sf::Clock clock;
  sf::RenderWindow window(sf::VideoMode(mainWindowWidth, mainWindowHeight), "Fireworks - by Victor Potasyev", sf::Style::Close); 

  //Initialization: textures, sprites, objects
  init(window);

  //Main loop
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      switch (event.type)
      {
      case(sf::Event::Closed):
        window.close();
        break;

      case(sf::Event::MouseButtonPressed): {
        float x = event.mouseButton.x;
        float y = event.mouseButton.y;
        FireworkStarter *fireworkStarter = new FireworkStarter(objectPool, window, x, y);
        objectPool.push_back(fireworkStarter);
        break;
      }

      default:
        break;
      }
    }

    window.clear(sf::Color::Red);
    window.draw(spriteBackground);

    //Draw Objects
    draw(window);

    //Update Objects
    sf::Time elapsed = clock.restart();
    float deltaTime = elapsed.asSeconds();
    update(deltaTime);

    window.draw(spriteMan);

    window.display();
  }

}





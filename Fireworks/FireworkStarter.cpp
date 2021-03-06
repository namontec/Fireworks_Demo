#include "pch.h"
#include "FireworkStarter.h"
#include "Tools.h"
#include <math.h>


FireworkStarter::FireworkStarter(std::list<Object*> &objectPool, sf::RenderWindow &window, float x, float y, Notify *notify)
  : Firework(window, x, y), objectPool_(objectPool), notify_(notify)
{
  startPosition = { x, static_cast<float>(getWindow().getSize().y) };
  spawnPosition = { x, y };

  setPosition(startPosition);
  setAcceleration({ 0, -600 });
  setGravity({ 0, 1 });
}


FireworkStarter::~FireworkStarter()
{
}

void FireworkStarter::update(float deltaTime)
{
  Firework::update(deltaTime);

  bool reachedSpawnPosition = getPosition().y < spawnPosition.y;
  if (reachedSpawnPosition) {
    spawnFireworks();
    destroyObject();
  }

}

void FireworkStarter::spawnFireworks()
{
  Tools tools;
  float pi = 3.1415926535f;
  float numberOfFireworks   = (float)tools.random(25, 50);
  float acceleration        = (float)tools.random(50, 200);
  int   wavesOfFireworks    = tools.random(1, 6);
  float gravitation         = 1.0f;
  float timeToLiveInSeconds = 2.0f;
  int   accVariant = 10;
  sf::Color color;
  sf::Vector2f direction;
  float angle;
  Firework *firework;

  color = sf::Color(tools.random(50, 255),
                    tools.random(50, 255),
                    tools.random(50, 255));

  for (int i = 1; i <= numberOfFireworks; i++) {
    for (int n = 1; n <= wavesOfFireworks; n++) {
      angle = 2 * pi * i / numberOfFireworks + ((float)tools.random(-1, 1) / 5);
      direction = { cos(angle), sin(angle) };
      
      timeToLiveInSeconds = 2.0f + (float)tools.random(-1, 1) / 10.0f;
      firework = new Firework(getWindow(), spawnPosition.x, spawnPosition.y, color, sf::seconds(timeToLiveInSeconds));

      firework->setAcceleration({ direction.x * acceleration / std::sqrtf ((float)n) + ((float)tools.random(-accVariant, accVariant)) ,
                                  direction.y * acceleration / std::sqrtf ((float)n) + ((float)tools.random(-accVariant, accVariant)) });
      firework->setGravity({ 0 , gravitation });
      objectPool_.push_back(firework);

    }
  }

  //Make contour lighting to watchman
  if (notify_) { notify_->notify(color, sf::seconds(timeToLiveInSeconds)); }
}

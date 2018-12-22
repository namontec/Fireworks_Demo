#include "pch.h"
#include "Firework.h"
#include "sfLine.h"


Firework::Firework(sf::RenderWindow &window,  float x, float y, sf::Color color, sf::Time timeToLive)
  : Object(window, x, y), timeToLive_(timeToLive)
{
  shape.setRadius(2.5f);
  float originPoint = shape.getRadius();
  shape.setOrigin(originPoint, originPoint);
  setColor(color);

  bool timeToLiveIsSet = (timeToLive_ != sf::Time::Zero);
  if (timeToLiveIsSet) { timer_.restart(); }
}


Firework::~Firework()
{
}



void Firework::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  sf::Time elapsed = timer_.getElapsedTime();

  //Draw trail
  sf::Vector2f startTrailPosition = getPosition();
  sf::Color trailColor;
  float maxThickness = 4;
  float i = 0;

  for (const auto &trail : trails) {
    i++;
    sf::Vector2f trailPosition = trail.first;

    trailColor = color_ - sf::Color(0, 0, 0, 255 * i / trails.size());
    sfLine line(startTrailPosition, trailPosition, trailColor, maxThickness * (trails.size() - i) / trails.size());
    target.draw(line);

    startTrailPosition = trailPosition;
  }

  //Drail trail head
  target.draw(shape);
}

void Firework::update(float deltaTime)
{
  Object::update(deltaTime);

  bool timeToLiveIsSet     = (timeToLive_ != sf::Time::Zero);
  if (timeToLiveIsSet) {
    sf::Time elapsed       = timer_.getElapsedTime();

    bool timeToDie         = (elapsed > timeToLive_);
    bool trailsDisappeared = (trails.size() == 0);
    if (timeToDie && trailsDisappeared) { destroyObject(); }
  }
}


void Firework::setPosition(sf::Vector2f position)
{
  Object::setPosition(position);
  shape.setPosition(position);

  addTrail(position);
}

void Firework::setColor(sf::Color color)
{
  color_ = color;

  shape.setFillColor(color_ + sf::Color(100, 100, 100) );
}

sf::Color Firework::getColor() const
{
  return color_;
}



void Firework::addTrail(sf::Vector2f position)
{
  sf::Time elapsed = timer_.getElapsedTime();

  bool readyToAddTrail = (elapsed - previousTrailTime) > trailMinTime;
  if  (readyToAddTrail) {
    previousTrailTime = elapsed;

    //Stop growing tail if firework is ready to die
    bool timeToLiveIsSet = (timeToLive_ != sf::Time::Zero);
    if (timeToLiveIsSet) {

      bool timeToDie = (elapsed > timeToLive_);
      if (timeToDie) {
        if (trails.size() > 0) { trails.pop_back(); }
        return;
      }
    }

    trails.push_front({ position, elapsed });

    bool trailReachedMaxSize = trails.size() > trailMaxLenght;
    if (trailReachedMaxSize) { trails.pop_back(); }
  }
}



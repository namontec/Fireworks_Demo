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
  float trailSize = trails.size();

  for (const auto &trailPosition : trails) {
    i++;

    trailColor = color_ - sf::Color(0, 0, 0, (sf::Uint8)(255 * i / trailSize));
    sfLine line(startTrailPosition, trailPosition, trailColor, maxThickness * (trailSize - i) / trailSize);
    target.draw(line);

    startTrailPosition = trailPosition;
  }

  //Draw trail head
  target.draw(shape);
}

void Firework::update(float deltaTime)
{
  Object::update(deltaTime);

  addTrail(getPosition());

  bool timeToLiveIsSet     = (timeToLive_ != sf::Time::Zero);
  if (timeToLiveIsSet) {
    sf::Time elapsed       = timer_.getElapsedTime();

    bool timeToDie         = (elapsed > timeToLive_);
    bool trailsDisappeared = (trails.empty());
    if (timeToDie && trailsDisappeared) { destroyObject(); }
  }
}


void Firework::setPosition(sf::Vector2f position)
{
  Object::setPosition(position);
  shape.setPosition(position);
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

    //Add new trail element
    trails.push_front(position);

    bool trailReachedMaxSize = trails.size() > (unsigned)trailMaxLenght;
    if (trailReachedMaxSize)
      trails.pop_back();


    //Stop growing tail if firework is ready to die
    bool timeToLiveIsSet = (timeToLive_ != sf::Time::Zero);
    if (timeToLiveIsSet) {

      bool timeToDie = (elapsed > timeToLive_);
      if (timeToDie) {
        if (!trails.empty()) { trails.pop_back(); }
        if (!trails.empty()) { trails.pop_back(); }
      }
    }

  }
}



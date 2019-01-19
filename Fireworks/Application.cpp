#include "pch.h"
#include "Application.h"


Application::Application(int width, int height)
  : mainWindowWidth_(width), mainWindowHeight_(height)
{
}


void Application::run()
{
  //sf::RenderWindow window(sf::VideoMode(mainWindowWidth_, mainWindowHeight_), "Fireworks - by Victor Potasyev", sf::Style::Close);
  window_.create(sf::VideoMode(mainWindowWidth_, mainWindowHeight_), "Fireworks - by Victor Potasyev", sf::Style::Close);
  
  //Initialization: textures, sprites, objects
  init();

  //Main loop
  mainLoop();

}

void Application::init()
{
  //if (!texture.loadFromFile("png\\sprites2x.png"))
  //  std::cout << "error reading texture" << std::endl;

  texture.loadFromMemory(spritesData, sizeof(spritesData));


  spriteBackground.setTexture(texture);
  spriteBackground.setTextureRect(sf::IntRect(0, 439, 1200, 800));

  spriteMan.setTexture(texture);
  spriteMan.setTextureRect(sf::IntRect(0, 1240, 1200, 96));
  spriteMan.setOrigin(0, 96);
  spriteMan.setPosition(0, mainWindowHeight_);

  spriteManLit.setTexture(texture);
  spriteManLit.setTextureRect(sf::IntRect(1, 1570, 154, 89));
  spriteManLit.setOrigin(0, 97);
  spriteManLit.setPosition(501, mainWindowHeight_);

  sittingMan = new Man(spriteMan, spriteManLit);

  clouds[0] = new Cloud(window_, -1400, -50);
  clouds[0]->sprite.setTexture(texture);
  clouds[0]->sprite.setTextureRect(sf::IntRect(0, 0, 1844, 438));
  clouds[0]->setAcceleration({ 20, 0 });

  clouds[1] = new Cloud(window_, -800, 50);
  clouds[1]->sprite.setTexture(texture);
  clouds[1]->sprite.setTextureRect(sf::IntRect(0, 0, 1844, 438));
  clouds[1]->setAcceleration({ 10, 0 });
  clouds[1]->sprite.setColor(sf::Color(255, 255, 255, 50));

  clouds[2] = new Cloud(window_, 600, 300);
  clouds[2]->sprite.setTexture(texture);
  clouds[2]->sprite.setTextureRect(sf::IntRect(0, 1337, 1004, 232));
  clouds[2]->setAcceleration({ 10, 0 });

  clouds[3] = new Cloud(window_, -300, 400);
  clouds[3]->sprite.setTexture(texture);
  clouds[3]->sprite.setTextureRect(sf::IntRect(0, 1337, 1004, 232));
  clouds[3]->setAcceleration({ 10, 0 });
  clouds[3]->sprite.setColor(sf::Color(255, 255, 255, 50));

  objectPool.push_back(clouds[1]);
  objectPool.push_back(clouds[3]);
  objectPool.push_back(clouds[2]);
  objectPool.push_back(clouds[0]);
}


void Application::update(float deltaTime)
{
  if (!objectPool.empty())
  {
    for (auto p = objectPool.begin(); p != objectPool.end(); p++)
    {

      //if time has come - perfom fixedUpdate()
      timeSinceLastFixedUpate += sf::seconds(deltaTime);

      //bool timeToFixedUpdate = timeSinceLastFixedUpate > fixedTimePerFrame;
      while (timeSinceLastFixedUpate > fixedTimePerFrame) {
        timeSinceLastFixedUpate -= fixedTimePerFrame;
        (*p)->fixedUpdate(fixedTimePerFrame.asSeconds());
      }

      //regular update
      (*p)->update(deltaTime);

      bool objectIsDestroyed = (*p)->isDestroyed();
      if (objectIsDestroyed) {
        delete (*p);
        p = objectPool.erase(p);

        bool pIsEndIterator = (p == objectPool.end());
        if (pIsEndIterator) break;
      }
    }
  }
}


void Application::draw()
{
  if (!objectPool.empty())
  {
    for (auto object : objectPool) {
      window_.draw(*object);
    }
  }
}

void Application::mainLoop()
{
  while (window_.isOpen())
  {
    sf::Event event;
    while (window_.pollEvent(event))
    {
      switch (event.type)
      {
      case(sf::Event::Closed):
        window_.close();
        break;

      case(sf::Event::MouseButtonPressed): {
        float x = (float)event.mouseButton.x;
        float y = (float)event.mouseButton.y;
        FireworkStarter *fireworkStarter = new FireworkStarter(objectPool, window_, x, y, sittingMan);

        objectPool.push_back(fireworkStarter);
        break;
      }

      default:
        break;
      }
    }

    window_.clear(sf::Color::Red);
    window_.draw(spriteBackground);


    //Update Objects
    sf::Time elapsed = clock.restart();
    float deltaTime = elapsed.asSeconds();
    update(deltaTime);

    //Draw Objects
    draw();

    //sittingMan.update();
    
    window_.draw(*sittingMan);

    window_.display();
  }
}


Application::~Application()
{
  delete sittingMan;
}

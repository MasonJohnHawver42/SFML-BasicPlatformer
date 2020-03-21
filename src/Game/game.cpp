#include "../Entity/mario.cpp"

double roundDec(double n, int d) { return std::floor(n * 100 + (1.0 / d))/100; }


void play() {

  std::cout << "game init" << '\n';

  int map[10][11] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  Grid<Tile> * gridMap = new Grid<Tile>(10, 11);

  for (int i = 0; i < gridMap->getRows(); i++) {
    for (int j = 0; j < gridMap->getCols(); j ++) {
      Tile * newTile = new Tile(map[i][j], map[i][j]);
      gridMap->put(newTile, i, j);
      std::cout << "Tile placed at (" << i << ", " << j << ")" << '\n';
    }
  }


  MarioWorld * world = new MarioWorld(gridMap);

  Mario * mario = new Mario();
  mario->setWorld(world);

  std::cout << "world created" << '\n';

  sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Demo Game");

  sf::Event event;

  sf::Font font;
  if (!font.loadFromFile("assets/BarcadeBrawl.ttf"))
  {
      // error...
  }

  BasicWorldViewer * camera = new BasicWorldViewer(world, window);
  camera->setTargetPos(mario->getPos());

  world->setViewer(camera);

  std::cout << "start" << '\n';

  while (window->isOpen()){

    while (window->pollEvent(event)){
      if (event.type == sf::Event::EventType::Closed)
        window->close();
    }

    window->clear();

    camera->updateWindow();

    sf::Text text("Pos:[x=" + std::to_string((int)roundDec(mario->getPos()->getX(), 2)) + ", y=" + std::to_string((int)roundDec(mario->getPos()->getY(), 2)) + "]"  , font);
    text.setCharacterSize(15);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setPosition(10,11);

    window->draw(text);

    window->display();

    double x = 0;
    double y = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { y += -500; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { y += 500; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { x += 500; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { x += -500; }

    mario->getAcc()->add(x, y);
    world->update();
  }

  return;
}

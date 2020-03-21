#include "pbEntity.cpp"

class Mario : public PhysicsBasedEntity{
private:
  double width;
  double height;

  double color;

public:
  Mario() : PhysicsBasedEntity() {
    width = 7.5;
    height = 10.0;
  }

  //getters

  double getWidth() { return width; }
  double getHeight() { return height; }

  //setters

  void setWidth(double w) { width = w; }
  void setHeight(double h) { height = h; }

  virtual void setWorld(MarioWorld * wrld) {
    world = wrld;
    world->setMario(this);
  }

  //other

  virtual bool isColliding() {

    double minCol = floor(pos->getX() / world->getTileWidth());
    double maxCol = ceil((pos->getX() + width) / world->getTileWidth());

    double minRow = floor(pos->getY() / world->getTileHeight());
    double maxRow = ceil((pos->getY() + height) / world->getTileHeight());

    bool col = 0;

    for (int i = minRow; i < maxRow; i ++) {
      for (int j = minCol; j < maxCol; j++) {
        if(world->getMap()->isValid(i, j)) {
          Tile * curr = world->getMap()->get(i, j);

          if(curr->isSolid()) {
            Vector<double> * tilePos = new Vector<double>(j, i);
            tilePos->mult(world->getTileWidth(), world->getTileHeight());

            Vector<double> * tileCenter = new Vector<double>(tilePos->getX(), tilePos->getY());
            tileCenter->add(world->getTileWidth() / 2.0, world->getTileHeight() / 2.0);

            Vector<double> * center = new Vector<double>(width, height);
            center->div(2.0);
            center->add(*pos);


            double xDiff, yDiff;
            if(center->getX() < tileCenter->getX()) {
              xDiff = tilePos->getX() - (pos->getX() + width);
            }
            else {
              xDiff = (tilePos->getX() + world->getTileWidth()) - pos->getX();
            }

            if(center->getY() < tileCenter->getY()) {
              yDiff = tilePos->getY() - (pos->getY() + height);
            }
            else {
              yDiff = (tilePos->getY() + world->getTileHeight()) - pos->getY();
            }

            if(abs(pos->getY() - tilePos->getY()) > abs(pos->getX() - tilePos->getX())) {
              pos->add(0, yDiff);
              vel->setY(0);
            }
            else {
              pos->add(xDiff, 0);
              vel->setX(0);
            }

            col =  1;

            delete tilePos, tileCenter, center;
          }


        }
      }
    }

    return col;

  }

  virtual void update() {

    double halfLife = .1;
    double frictionRate = pow(.5, getElapsedTime() / halfLife );

    if(isColliding()) {
      color = 200;
      getVel()->mult(frictionRate);
    }
    else { color = 255; }

    acc->add(0, 200);

    applyAcc();
    applyVel();

    restartClock();

  }

  virtual void draw() {
    CoordinateBasedViewer * cam = world->getViewer();
    sf::RenderWindow * window = cam->getWindow();

    Vector<double> * mappedPos = new Vector<double>(pos->getX(), pos->getY());
    mappedPos->sub(*cam->getPos());

    Vector<double> * transform = new Vector<double>(window->getSize().x / cam->getWidth(), window->getSize().y / cam->getHeight());

    mappedPos->mult(*transform);
    double mappedWidth = width * transform->getX();
    double mappedHeight = height * transform->getY();

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(mappedWidth, mappedHeight));
    rectangle.setPosition(mappedPos->getX(), mappedPos->getY());
    rectangle.setFillColor(sf::Color(255, color, color));

    rectangle.setOutlineColor(sf::Color(255, 255, 53));
    rectangle.setOutlineThickness(5);

    //window->draw(rectangle);

    double maxArrowLen = 28;
    double maxArrowWidth = 1.5;

    double dis = vel->getMag();

    double arrowLen = dis;
    arrowLen = (arrowLen * maxArrowLen) / (arrowLen + (maxArrowLen * 2));

    double arrowWidth = arrowLen * .05;
    //arrowWidth = (arrowWidth * maxArrowWidth) / (arrowWidth + (maxArrowWidth * 100));
    arrowWidth = max(arrowWidth, .5);

    Vector<double> * arrowPoint = new Vector<double>(vel->getX(), vel->getY());
    arrowPoint->mult(arrowLen / dis);

    Vector<double> * perpVel = new Vector<double>(vel->getX(), vel->getY());
    perpVel->perp();
    perpVel->mult(arrowWidth / dis);

    sf::ConvexShape convex;
    convex.setPointCount(4);

    double maxColor = 256;
    double arrowColor = dis;
    arrowColor = (arrowColor * maxColor) / (arrowColor + (maxColor * 1));
    arrowColor += 256 - maxColor;

    convex.setFillColor(sf::Color(arrowColor, 0, 256 - (arrowColor)));

    int order[4] = {0, 1, 3, 2};

    for(int i = 0; i < 4; i++) {

      Vector<double> * point;
      int flip = ((i % 2)*2) - 1;

      if(i < 2) {
        point = new Vector<double>(flip, flip);
        point->mult(*perpVel);
      }
      else {
        point = new Vector<double>(flip, flip);
        point->mult(*perpVel);
        point->add(*arrowPoint);
      }

      point->add(*pos);
      point->add(width / 2.0, height / 2.0);
      point->sub(*cam->getPos());
      point->mult(*transform);

      convex.setPoint(order[i], sf::Vector2f(point->getX(), point->getY()));
      delete point;
    }

    window->draw(rectangle);
    window->draw(convex);

    delete mappedPos, transform, arrowPoint, arrowLen;
  }
};

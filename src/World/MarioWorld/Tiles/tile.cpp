#include"../../world.cpp"

class Tile {
private:
  bool solid;
  bool visable;

public:
  Tile(bool s, bool v) {
    solid = s;
    visable = v;
  }

  Tile() {
    solid = 0;
    visable = 0;
  }

  // getters

  bool isSolid() { return solid; }
  bool isVisable() { return visable; }

  //setters

  void makeSolid(bool val) { solid = val; }
  void makeVisable(bool val) { visable = val; }

  // virtuals

  virtual void draw(sf::RenderWindow * win, Vector<double> mappedTilePos, sf::Vector2f size) {

    sf::RectangleShape rectangle;
    rectangle.setSize(size);
    rectangle.setPosition(mappedTilePos.getX(), mappedTilePos.getY());

    sf::Color fillColor(204, 204, 255);
    rectangle.setFillColor(fillColor);

    win->draw(rectangle);

    double borderThickness = .1;

    sf::Vector2f newSize = size;
    newSize.x *= (1 - borderThickness);
    newSize.y *= (1 - borderThickness);

    Vector<double> newPos = mappedTilePos;
    newPos.add((size.x - newSize.x) / 2.0, (size.y - newSize.y) / 2.0);

    sf::RectangleShape rectangle2;
    rectangle2.setSize(newSize);
    rectangle2.setPosition(newPos.getX(), newPos.getY());

    sf::Color fillColor2(255, 255, 255);
    rectangle2.setFillColor(fillColor2);

    win->draw(rectangle2);

  }

};

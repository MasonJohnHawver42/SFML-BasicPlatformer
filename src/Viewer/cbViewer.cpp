#include "viewer.cpp"
#include "../vector.cpp"

class CoordinateBasedViewer : public Viewer {
protected:
  Vector<double> * pos;

  double width;
  double height;

public:
  CoordinateBasedViewer(sf::RenderWindow * win) : Viewer(win) {
    pos = new Vector<double>(0, 0);
    width = 400;
    height = 225;
  }

  CoordinateBasedViewer() : Viewer() {
    pos = new Vector<double>(0, 0);
    width = 100;
    height = 100;
  }
  //getters

  Vector<double> * getPos() { return pos; }

  double getHeight() { return height; }
  double getWidth() { return width; }

  //setters

  void setPos(double x, double y) {
    pos->setX(x);
    pos->setY(y);
  }

  void setWidth(double w) { width = w; }
  void setHeight(double h) { height = h; }

  void setPos(Vector<double> * p) { pos = p; }

};

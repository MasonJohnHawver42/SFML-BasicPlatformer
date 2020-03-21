#include"basicWorldEntity.cpp"

class CoordinateBasedEntity : public BasicWorldEntity {
protected:
  Vector<double> * pos;

public:

  CoordinateBasedEntity() : BasicWorldEntity() {
    pos = new Vector<double>(10, 10);
  }

  //getters

  Vector<double> * getPos() { return pos; }

  //setters

  void setPos(Vector<double> * p) { pos = p; }
  void setPos(double x, double y) {
    pos->setX(x);
    pos->setY(y);
  }

};

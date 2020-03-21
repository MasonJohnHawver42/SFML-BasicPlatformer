#include "cbEntity.cpp"

class PhysicsBasedEntity : public CoordinateBasedEntity {
protected:
  Vector<double> * vel;
  Vector<double> * acc;

  double maxSpeed;
  double maxAcc;

  double mass;

  // both are some amt of gameunits per second

  sf::Clock * masterClock;


public:
  PhysicsBasedEntity() : CoordinateBasedEntity() {
    vel = new Vector<double>(0, 0);
    acc = new Vector<double>(0, 0);

    maxSpeed = 1000;
    maxAcc = 1000;

    masterClock = new sf::Clock();
  }

  //getters

  Vector<double> * getVel() { return vel; }
  Vector<double> * getAcc() { return acc; }

  double getMaxSpeed() { return maxSpeed; }
  double getMaxAcc() { return maxAcc; }

  double getElapsedTime() { return masterClock->getElapsedTime().asSeconds(); }

  //setters

  void setVel(Vector<double> v) { vel->setX(v.getX()); vel->setY(v.getY()); }
  void setAcc(Vector<double> a) { acc->setX(a.getX()); acc->setY(a.getY()); }

  void setMaxSpeed(double ms) { maxSpeed = abs(ms); }
  void setMaxAcc(double a) { maxAcc = abs(a); }

  //modifyers

  void restartClock() { masterClock->restart(); }

  void applyVel() {
    double t = getElapsedTime();
    Vector<double> * v = new Vector<double>(t, t);
    v->mult(*vel);
    pos->add(*v);

    delete v;
  }

  void applyAcc() {
    acc->limitMag(maxAcc);

    double t = getElapsedTime();
    Vector<double> * a = new Vector<double>(t, t);
    a->mult(*acc);

    vel->add(*a);
    vel->limitMag(maxSpeed);
    acc->mult(0);

    delete a;
  }

  virtual void update() {}

};

#include "cbViewer.cpp"

class FollowingVeiwer : public CoordinateBasedViewer {
private:
  Vector<double> * target;

  double horizontalBound;
  double verticalBound;

  Vector<double> * vel;
  Vector<double> * acc;

  sf::Clock * masterClock;

public:
  FollowingVeiwer(Vector<double> * t, sf::RenderWindow * win) : CoordinateBasedViewer(win) {
    target = t;

    horizontalBound = 10;
    verticalBound = 10;

    vel = new Vector<double>(0, 0);
    acc = new Vector<double>(0, 0);

    masterClock = new sf::Clock();
  }
  FollowingVeiwer(sf::RenderWindow * win) : CoordinateBasedViewer(win) {
    target = new Vector<double>(0, 0);

    horizontalBound = 120;
    verticalBound = 60;

    vel = new Vector<double>(0, 0);
    acc = new Vector<double>(0, 0);

    masterClock = new sf::Clock();
  }
  FollowingVeiwer() : CoordinateBasedViewer() {
    target = new Vector<double>(0, 0);

    horizontalBound = 10;
    verticalBound = 10;

    vel = new Vector<double>(0, 0);
    acc = new Vector<double>(0, 0);

    masterClock = new sf::Clock();
  }

  //getters

  Vector<double> * getTargetPos() { return target; }

  double getHorizontalBound() { return horizontalBound; }
  double getVertical() { return verticalBound; }

  double getElapsedTime() { return masterClock->getElapsedTime().asSeconds(); }

  //setters

  void setTargetPos(Vector<double> * t) { target = t; }

  void setHorizontalBound(double h) {horizontalBound = h;}
  void setVerticalBound(double v) { verticalBound = v; }


  //other

  void applyVel(double t) {
    Vector<double> * v = new Vector<double>(t, t);
    v->mult(*vel);
    pos->add(*v);

    delete v;
  }

  void applyAcc(double t) {
    Vector<double> * a = new Vector<double>(t, t);
    a->mult(*acc);
    vel->add(*a);

    acc->mult(0);
    delete a;
  }

  void updateAcc() {
    Vector<double> * dir = new Vector<double>(target->getX(), target->getY());
    dir->sub(*pos);
    dir->sub(width / 2.0, height / 2.0);
    dir->mult(10);
    acc->add(*dir);
  }

  virtual void updatePos() {

    /**
    double t = getElapsedTime();

    updateAcc();
    applyAcc(t);
    applyVel(t);

    masterClock->restart();
    **/


    Vector<double> * boundPos = new Vector<double>(pos->getX(), pos->getY());
    boundPos->add(width / 2.0, height / 2.0);
    boundPos->sub(horizontalBound / 2.0, verticalBound/ 2.0);

    double horizontalShift = 0;
    horizontalShift += ( target->getX() >= boundPos->getX() ? 0 : target->getX() - boundPos->getX());

    horizontalShift += ( target->getX() <= boundPos->getX() + horizontalBound ? 0 : target->getX() - (boundPos->getX() + horizontalBound));

    double verticalShift = 0;
    verticalShift += ( target->getY() >= boundPos->getY() ? 0 : target->getY() - boundPos->getY());
    verticalShift += ( target->getY() <= boundPos->getY() + verticalBound ? 0 : target->getY() - (boundPos->getY() + verticalBound));

    pos->add(horizontalShift, verticalShift);

    delete boundPos;

  }
};

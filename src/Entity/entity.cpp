#include <SFML/Graphics.hpp>
#include <math.h>

using namespace std;

class Entity {
private:
  int id;
  static int next_id;

public:
  Entity() {
    id = next_id;
    next_id++;
  }

  // getter --

  int getId() { return id; }

  // virtual

  virtual void start() {}
  virtual void update() {}
  virtual void draw() {};

  virtual bool equal(Entity * other) {
    return id == other->getId();
  }

};

int Entity::next_id = 0;

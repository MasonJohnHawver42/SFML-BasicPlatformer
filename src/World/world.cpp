#include "../Viewer/followingVeiwer.cpp"

class World {
private:

  int id;
  int static next_id;

  CoordinateBasedViewer * viewer;

public:

  World() {
    id = next_id;
    next_id++;
  }

  //getters

  int getId() { return id; }
  CoordinateBasedViewer * getViewer() { return viewer; }

  //setters

  void setViewer(CoordinateBasedViewer * v) { viewer = v; }

  //virtuals

  virtual void start() {}
  virtual void update() {}

  virtual bool equal(World other) {
    return (id == other.getId());
  }

};

int World::next_id = 0;

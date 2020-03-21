#include"../Viewer/worldViewer.cpp"

class BasicWorldEntity : public Entity {
protected:
  MarioWorld * world;

public:
  BasicWorldEntity(MarioWorld * wrld) : Entity() {
    world = wrld;
  }

  BasicWorldEntity() : Entity() {
    world = nullptr;
  }

  //getters

  MarioWorld * getWorld() { return world; }

  //setters

  virtual void setWorld(MarioWorld * w) { world = w; }

  //virtuals

  virtual void update() {}

};

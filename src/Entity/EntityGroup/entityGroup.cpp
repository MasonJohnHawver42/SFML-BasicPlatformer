#include "../entity.cpp"

class EntityGroup {
protected:
  int correctIndex(int index) {
    int n = getEntityNum();
    return min(max(index, 0), n);
  }

  int id;
  int static next_id;

public:

  EntityGroup() {
    id = next_id;
    next_id++;
  }

  //getters

  virtual int getEntityNum() { return 0; }
  virtual Entity * getEntity(int index) { return nullptr; }

  int getId() { return id; }

  //modifyers

  virtual bool addEntity(Entity * e) { return 0; }

  virtual bool removeEntity(Entity * e) { return 0; }
  virtual bool removeEntity(int Index) { return 0; }

  //other

  virtual void update() {}
  virtual void start() {}
  virtual void draw(sf::RenderWindow * window) {}

  //comparers

  bool equal(EntityGroup * other) {
    return id == other->getId();
  }

};

int EntityGroup::next_id = 0;

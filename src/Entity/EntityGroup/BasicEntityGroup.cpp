#include "entityGroup.cpp"

class BasicEntityGroup : public EntityGroup {
protected:
  vector<Entity*> * group;

public:
  BasicEntityGroup() : EntityGroup() {
    group = new vector<Entity*>();
  }

  //getters

  virtual int getEntityNum() { return group->size(); }
  virtual Entity * getEntity(int index) { group->at(correctIndex(index)); }

  //modifyers

  bool addEntity(Entity * newEntity) {
      for(int i = 0; i < group->size(); i++) {
        Entity * other = group->at(i);

        if(newEntity->equal(other)) {
          return 0;
        }
      }

      group->push_back(newEntity);

      return 1;
    }

  virtual bool removeEntity(int index) {
    group->erase(group->begin() + correctIndex(index));
    return 1;
  }

  virtual bool removeEntity(Entity * oldEntity) {
    for(int i = 0; i < group->size(); i++) {
      Entity * curr = group->at(i);
      if(oldEntity->equal(curr)) { removeEntity(i); return 1;}
    }

    return 0;
  }

  //other

  virtual void update() {
    for(int i = 0; i < group->size(); i++) {
      Entity * curr = group->at(i);
      curr->update();
    }
  }

  virtual void start() {
    for(int i = 0; i < group->size(); i++) {
      Entity * curr = group->at(i);
      curr->start();
    }
  }

  virtual void draw(sf::RenderWindow * window) {
    for(int i = 0; i < group->size(); i++) {
      Entity * curr = group->at(i);
      curr->draw();
    }
  }

};

#include"../../Entity/EntityGroup/BasicEntityGroup.cpp" //for the monsters
#include "grid.cpp"

class MarioWorld : public World {
protected:
  Entity * mario;

  Grid<Tile> * map;

  double tileWidth;
  double tileHeight;

  sf::Clock * masterClock;

public:

  MarioWorld() : World() {
    map = new Grid<Tile>(200, 200);

    for (int i = 0; i < map->getRows(); i++) {
      for (int j = 0; j < map->getCols(); j ++) {
        Tile * newTile = new Tile(1, 1);
        map->put(newTile, i, j);
        std::cout << "Tile placed at (" << i << ", " << j << ")" << '\n';
      }
    }

    tileWidth = 10;
    tileHeight = 10;

    masterClock = new sf::Clock();
  }

  MarioWorld(Grid<Tile> * m) : World() {
    map = m;

    tileWidth = 10;
    tileHeight = 10;

    masterClock = new sf::Clock();
  }

  // getters

  Grid<Tile> * getMap() { return map; }

  double getElapsedTime() { return masterClock->getElapsedTime().asSeconds(); }

  double getTileWidth() { return tileWidth; }
  double getTileHeight() { return tileHeight; }

  Entity * getMario() { return mario; }

  //setters

  void setTileWidth(double w) { tileWidth = w; }
  void setTileHeight(double h) { tileHeight = h; }

  void setMario(Entity * m) { mario = m; }

  //other

  virtual void start() {  }
  virtual void update() { mario->update(); masterClock->restart(); }

};

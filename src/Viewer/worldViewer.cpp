#include "../World/MarioWorld/marioWorld.cpp"

class BasicWorldViewer : public FollowingVeiwer {
protected:
  MarioWorld * world;

  Vector<double> * convertWPtoSP(Vector<double> * wp) {
    Vector<double> * sp = new Vector<double>(wp->getX(), wp->getY());
    sp->sub(*pos);
    sp->div(width, height);
    sp->mult(window->getSize().x, window->getSize().y);

    return sp;
  }

public:
  BasicWorldViewer(MarioWorld * wrld, sf::RenderWindow * win) : FollowingVeiwer(win) { world = wrld; }
  BasicWorldViewer(MarioWorld * wrld) : FollowingVeiwer() { world = wrld; }

  BasicWorldViewer() : FollowingVeiwer() { world = new MarioWorld(); }

  //getters

  MarioWorld * getWorld() { return world; }

  //setters

  void setWorld(MarioWorld * w) { world = w; }

  //other

  void drawMap() {

        double warpedTileWidth = world->getTileWidth() * (window->getSize().x / width);
        double warpedTileHeight = world->getTileHeight() * (window->getSize().y / height);

        sf::Vector2f * size = new sf::Vector2f(warpedTileWidth, warpedTileHeight);

        double minCol = floor(pos->getX() / world->getTileWidth());
        double maxCol = ceil((pos->getX() + width) / world->getTileWidth());
        double minRow = floor(pos->getY() / world->getTileHeight());
        double maxRow = ceil((pos->getY() + height) / world->getTileHeight());

        for (int i = minRow; i <= maxRow; i++) {
          for (int j = minCol; j <= maxCol; j++) {
            if ( world->getMap()->isValid(i, j) ) {

              Tile * curr = world->getMap()->get(i, j);

              if (curr->isVisable()) {

                //getting world pos of tile

                Vector<double> * tilePos = new Vector<double>(j, i);
                tilePos->mult(world->getTileWidth(), world->getTileHeight());

                //coverting world pos to screen pos for the tile pos

                tilePos->sub(*pos);
                tilePos->div(width, height);
                tilePos->mult(window->getSize().x, window->getSize().y);

                //drawin it

                curr->draw(window, *tilePos, *size);

                //deallocation of mem

                delete tilePos;
              }

            }
          }
        }

        //deallocation of mem

        delete size;
  }

  virtual void updateWindow() {
      updatePos();

      drawMap();
      world->getMario()->draw();
   }

};

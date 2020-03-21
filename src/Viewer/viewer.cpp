#include <SFML/Graphics.hpp>

class Viewer {
protected:
  sf::RenderWindow * window;

public:
  Viewer(sf::RenderWindow * w) {
    window = w;
  }

  Viewer() {}

  //getters

  sf::RenderWindow * getWindow() { return window; }

  //setters

  void setWindow(sf::RenderWindow * w) { window = w; }

  //other

  virtual void updateWindow() {}

};

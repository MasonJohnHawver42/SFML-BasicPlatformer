#include"Tiles/tile.cpp"

template<class T>
class Grid
{
protected:
  T*** board;

  int rows;
  int cols;

public:
  Grid()
  {
    rows = 10;
    cols = 10;

    board = new T**[10];

    for (int i = 0; i < 10; ++i) {
      board[i] = new T*[10];
    }
  }

  Grid(int r, int c)
  {
    rows = r;
    cols = c;

    board = new T**[r];

    for (int i = 0; i < r; ++i) {
      board[i] = new T*[c];
    }
  }

  int getRows();
  int getCols();

  T * get(Vector<int> loc);
  T * get(int row, int col);

  void put(T * obj, Vector<int> loc);
  void put(T * obj, int row, int col);

  bool isValid(Vector<int> loc);
  bool isValid(int row, int col);

  void toString();


};

//getters

template<class T> int Grid<T>::getRows() { return rows; }
template<class T> int Grid<T>::getCols() { return cols; }

template<class T> T * Grid<T>::get(Vector<int> loc) {
  if(isValid(loc)) {
    return board[loc.getY()][loc.getX()];
  }
}
template<class T> T * Grid<T>::get(int row, int col) {
  if(isValid(row, col)) {
    return board[row][col];
  }
}

//setters

template<class T> void Grid<T>::put(T * obj, Vector<int> loc)
{
  if(isValid(loc)) {
    board[loc.getY()][loc.getX()] = obj;
  }
}
template<class T> void Grid<T>::put(T * obj, int row, int col)
{
  if(isValid(row, col) && obj) {
    board[row][col] = obj;
  }
}

//other

template<class T> bool Grid<T>::isValid(Vector<int> loc) {
  return (0 <= loc.getY() && getRows() > loc.getY()) && (0 <= loc.getX() && getCols() > loc.getX());
}
template<class T> bool Grid<T>::isValid(int row, int col) {
  return (0 <= row && getRows() > row) && (0 <= col && getCols() > col);
}

#ifndef POINT_H
#define POINT_H

class Point {
  public:

    int posX;
    int posY;
    
    Point(int x, int y): posX(x), posY(y) {}

    bool operator==(const Point& p) {
      return posX == p.posX && posY == p.posY;
    }
};

#endif

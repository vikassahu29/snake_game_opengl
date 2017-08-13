#ifndef GAME_H
#define GAME_H

#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "Config.h"
#include "Direction.h"
#include "Point.h"
#include "Renderer.h"



class Game {

private:
  std::shared_ptr<Config> _config;
  std::unique_ptr<Renderer> _renderer;
  Direction _snakeDirection;
  std::vector<Point> _snake;
  Point _baitPos;
  bool _isOver;
  int _score;

  std::unique_ptr<std::thread> _snakeMoveThread;
  std::recursive_mutex _mutex;

  bool isColliding();
  Point createBaitPos();

  public:

    Game(int rows, int columns);

    void startGame();
    void renderGame();
    void processKey(unsigned char key);

};

#endif

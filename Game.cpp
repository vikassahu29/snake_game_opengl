#include <chrono>
#include <cstdlib>
#include <ctime>
#include "Config.h"
#include "Game.h"

namespace {
  Point nextPointFromDir(Point& p, Direction dir) {
    switch(dir) {
      case Direction::Right:
        return Point(p.posX + 1, p.posY);
      case Direction::Left:
        return Point(p.posX - 1, p.posY);
      case Direction::Up:
        return Point(p.posX, p.posY + 1);
      case Direction::Down:
        return Point(p.posX, p.posY - 1);
    }
  }
}

Game::Game(int rows, int columns): _baitPos({-1,-1}) {
  std::srand(time(0));
  _config = std::make_shared<Config>(rows, columns);
  _renderer = std::make_unique<Renderer>(_config);
  _isOver = false;
  _snake.emplace_back(columns/2, rows/2);
  _snake.emplace_back(columns/2, rows/2 - 1);
  _baitPos = createBaitPos();

  _snakeMoveThread = std::make_unique<std::thread>([&]() {
    while (!_isOver) {
      _mutex.lock();
      if (isColliding()) {
        _score = _snake.size() - 2;
        _isOver = true;
        break;
      } else if (_baitPos == _snake.back()) {
        _snake.push_back(nextPointFromDir(_baitPos, _snakeDirection));
        _baitPos = createBaitPos();
      } else {
        int len = _snake.size();
        for(int i = 0; i < len - 1; i++) {
          _snake[i].posX = _snake[i + 1].posX;
          _snake[i].posY = _snake[i + 1].posY;
        }
        _snake[len - 1] = nextPointFromDir(_snake.back(), _snakeDirection);
      }
      _mutex.unlock();

      /*
       * Setting sleep time for thread.
       * Change this time to increase - decrease difficulty.
       */
      std::this_thread::sleep_for (std::chrono::milliseconds(100));
    }
  });
  _snakeMoveThread->detach();
}

void Game::startGame() {
  _snakeDirection = Direction::Right;
}

void Game::renderGame() {
  if (_isOver) {
    _renderer->drawResult(_score);
  } else {
    _renderer->drawGrid();
    _mutex.lock();
    _renderer->drawSnake(_snake);
    _renderer->drawBait(_baitPos);
    _mutex.unlock();
  }
}

void Game::processKey(unsigned char key) {
  if (key > 91) {
    key -= 32;
  }
  switch (key) {
    case 'W':
      if (_snakeDirection != Direction::Down) {
        _snakeDirection = Direction::Up;
      }
      break;
    case 'A':
      if (_snakeDirection != Direction::Right) {
        _snakeDirection = Direction::Left;
      }
      break;
    case 'S':
      if (_snakeDirection != Direction::Up) {
        _snakeDirection = Direction::Down;
      }
      break;
    case 'D':
      if (_snakeDirection != Direction::Left) {
        _snakeDirection = Direction::Right;
      }
      break;
    case 27:
      exit(0);
    default:
      break;
  }
}

bool Game::isColliding() {

  auto head =  _snake.back();
  if (head.posX == 0 || head.posX == _config->columns() - 1 ||
      head.posY == 0 || head.posY == _config->rows() - 1) {
    return true;
  }

  for (int i = _snake.size() - 2; i > -1; i--) {
    Point& p = _snake[i];
    if (head.posX == p.posX && head.posY == p.posY) {
      return true;
    }
  }
  return false;
}

Point Game::createBaitPos() {
  int r = _config->rows();
  int c = _config->columns();

  Point & head = _snake.back();

  int x = std::rand() % (c - 1) + 1;
  int y = std::rand() % (r - 1) + 1;

  if (x == head.posX && y == head.posY) {
    return Game::createBaitPos();
  } else {
    return Point(x, y);
  }

}

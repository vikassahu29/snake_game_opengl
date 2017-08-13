#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>
#include "Config.h"
#include "Point.h"

class Renderer {
  private:
    std::shared_ptr<Config> _config;
  public:

    Renderer(std::shared_ptr<Config>);

    void drawGrid();

    void drawSnake(const std::vector<Point>& snake);

    void drawBait(const Point& baitPos);
    
    void drawResult(int score);

};

#endif

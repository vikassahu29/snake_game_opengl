#include <GL/glut.h>
#include "Renderer.h"

namespace {
  void drawSquare(int x, int y) {
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
  }

  void drawFilledSquare(int x, int y) {
    glBegin(GL_POLYGON);
    drawSquare(x, y);
    glEnd();
  }

  void drawEmptySquare(int x, int y) {
    glBegin(GL_LINE_LOOP);
    drawSquare(x, y);
    glEnd();
  }

}
Renderer::Renderer(std::shared_ptr<Config> config): _config(config) {

}

void Renderer::drawGrid() {
  int r = _config->rows();
  int c = _config->columns();

  /*
   * Draw Border
   */

  glLineWidth(2.0);
  glColor3f(1.0, 0.0, 0.0);

  int i = 0;
  int j = 0;
  while (i < c) {
    drawEmptySquare(i, 0);
    drawEmptySquare(i, r - 1);
    i++;
  }

  while (j < r) {
    drawEmptySquare(0, j);
    drawEmptySquare(c - 1, j);
    j++;
  }

  /*
   * Draw Grid
   */

  glLineWidth(1.0);
  glColor3f(0.6, 0.6, 0.6);


  for (i = 1; i < c - 1 ; i++) {
    for (j = 1; j < r - 1; j++) {
      drawEmptySquare(i,j);
    }
  }

}
void Renderer::drawSnake(const std::vector<Point>& snake) {
  glColor3f(0.6,1.0,0.6);
  for (auto p : snake) {
    drawFilledSquare(p.posX, p.posY);
  }
}
void Renderer::drawBait(const Point& p) {
  glColor3f(0.6,0.6,1.0);
  drawFilledSquare(p.posX, p.posY);
}

void Renderer::drawResult(int score) {
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(_config->columns() * 0.45, _config->rows()/2);
    std::string message = "Score is " + std::to_string(score) +". Game Over";
    for ( int i = 0; i < message.length(); ++i ) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
    glPopMatrix();
}

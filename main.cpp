#include <GL/glut.h>
#include "Game.h"

namespace {
  static std::shared_ptr<Game> game;
  static const int GRID_ROWS = 50;
  static const int GRID_COLUMNS = 50;
}

void keyboardCallback(unsigned char key, int x, int y) {
  game->processKey(key);
}

void timerCallback(int a) {
  glutPostRedisplay();
  glutTimerFunc(100, timerCallback, 0);
}

void display() {
  // Clear buffer
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT);

  // Render contents
  game->renderGame();
  glFlush();

  // Swap back and front buffer
  glutSwapBuffers();
}

int main(int argc, char **argv) {

  /*
   * Initialize glut window
   */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutCreateWindow("Snake Game");
  glutInitWindowSize(500, 500);

  game = std::make_shared<Game>(GRID_ROWS, GRID_COLUMNS);
  game->startGame();

  // Register display callback
  glutDisplayFunc(display);

  // Register reshape callback
  glutReshapeFunc([](int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, GRID_COLUMNS, 0.0, GRID_ROWS, -1, 1);
    glMatrixMode(GL_MODELVIEW);
  });

  // Register timer callback
  glutTimerFunc(0, timerCallback, 0);

  // Register keyboard callback
  glutKeyboardFunc(keyboardCallback);

  // Start main loop
  glutMainLoop();
  return 0;
}

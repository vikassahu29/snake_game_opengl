#include "Config.h"

Config::Config(int rows, int columns) {
  _rows = rows;
  _columns = columns;
}

int Config::rows() {
  return _rows;
}

int Config::columns() {
  return _columns;
}

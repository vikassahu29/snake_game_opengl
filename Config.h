#ifndef CONFIG_H
#define CONFIG_H

class Config {
  private:
    int _rows;
    int _columns;
  public:
    Config(int rows, int columns);

    int rows();
    int columns();
};

#endif

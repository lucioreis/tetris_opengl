
#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include "Tetris.h"

void setup(bool options[]);

namespace game{
  void game(int key);

  void handle_key(unsigned char, int, int);

  void handle_special_key(int, int, int);

  void drawSquare(int, int);

  void drawSquares(const Tetris&, int, int);

  void display(void);

  void init(void);

  void reshape(int, int);

  void timer(int);

  int start(bool options[]);

  void text(const std::string &texto, int x, int y, double tamanhoX, double tamanhoY); 
}

#include "game.h"

int main(int argc, char *argv[]) {
  argv; argc;
  Game game;
  game.init();
  game.update();
  game.release();
  
  return 0;
}

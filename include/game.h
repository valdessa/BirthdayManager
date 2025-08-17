/**
 * @file   game.h
 * @brief  game header file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */
#ifndef __GAME_H__
#define __GAME_H__ 1

#include <SDL.h>
#include <stdio.h>
#include <math.h>
#include <string>


#include "my_imgui.h"
#include "clock.h"
#include "entity.h"
#include "database.h"
#include "kirby.h"

class Game {
 public:
  Game();
  ~Game();
  void init();
  void update();
  void release(); //change to destructor

  bool close = false;
  SDL_Event event;
  RenderWindow window;
  MyImGui my_imgui;
  Database my_database;
  Clock my_clock;
  Kirby kirby;
  Sprite sprite;
  Entity entity;

};



#endif
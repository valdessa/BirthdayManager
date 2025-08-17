/**
 * @file   kirby.h
 * @brief  kirby header file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */

#ifndef __KIRBY_H__
#define __KIRBY_H__ 1

#include "sprite.h"
#include "sound.h"

namespace {
  const char* kirby_paths1[] = { //25
    "../data/sprites/kirby_painting/project1.png", 
    "../data/sprites/kirby_painting/project2.png",
    "../data/sprites/kirby_painting/project3.png",
    "../data/sprites/kirby_painting/project4.png", 
    "../data/sprites/kirby_painting/project5.png",
    "../data/sprites/kirby_painting/project6.png",
    "../data/sprites/kirby_painting/project7.png", 
    "../data/sprites/kirby_painting/project8.png",
    "../data/sprites/kirby_painting/project9.png",
    "../data/sprites/kirby_painting/project10.png", 
    "../data/sprites/kirby_painting/project11.png",
    "../data/sprites/kirby_painting/project12.png",
    "../data/sprites/kirby_painting/project13.png", 
    "../data/sprites/kirby_painting/project14.png", 
    "../data/sprites/kirby_painting/project15.png", 
    "../data/sprites/kirby_painting/project16.png", 
    "../data/sprites/kirby_painting/project17.png", 
    "../data/sprites/kirby_painting/project18.png", 
    "../data/sprites/kirby_painting/project19.png", 
    "../data/sprites/kirby_painting/project20.png", 
    "../data/sprites/kirby_painting/project21.png", 
    "../data/sprites/kirby_painting/project22.png", 
    "../data/sprites/kirby_painting/project23.png", 
    "../data/sprites/kirby_painting/project24.png",
    "../data/sprites/kirby_painting/project25.png", 
  };

  const char* kirby_paths2[] = { //10
    "../data/sprites/kirby_walking/Sprite-0001.png", 
    "../data/sprites/kirby_walking/Sprite-0002.png",
    "../data/sprites/kirby_walking/Sprite-0003.png",
    "../data/sprites/kirby_walking/Sprite-0004.png", 
    "../data/sprites/kirby_walking/Sprite-0005.png",
    "../data/sprites/kirby_walking/Sprite-0006.png",
    "../data/sprites/kirby_walking/Sprite-0007.png", 
    "../data/sprites/kirby_walking/Sprite-0008.png",
    "../data/sprites/kirby_walking/Sprite-0009.png",
    "../data/sprites/kirby_walking/Sprite-0010.png", 
  };

  const char* kirby_paths3[] = { //6
    "../data/sprites/paint/Sprite-0001.png", 
    "../data/sprites/paint/Sprite-0002.png",
    "../data/sprites/paint/Sprite-0003.png",
    "../data/sprites/paint/Sprite-0004.png", 
    "../data/sprites/paint/Sprite-0005.png",
    "../data/sprites/paint/Sprite-0006.png", 
  };
}

enum Phase{
 noAnimation = 0,
 climbing = 1,
 painting = 2,
 walking = 3,
};

class Kirby : public Sprite {
 public:
  Kirby();
  ~Kirby();

  void init(float p_x, float p_y);
  
  void activateAnimation();
  void update(SDL_Renderer* rend, uint32_t dt);

  void free();

  //Vector of Kirby
  Vector* vector_KirbyPainting;
  Vector* vector_KirbyWalking;
  Vector* vector_Paint;


  MyTexture textures;

  Phase animation;
  bool finish;
  char todaysBirthday[100] = "\0";

  Sound sound;
  Mix_Chunk *rightStep_;
  Mix_Chunk *leftStep_;
};




#endif
/**
 * @file   kirby.cc
 * @brief  kirby file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */

#include "kirby.h"

Kirby::Kirby() {
  animation = noAnimation;
  finish = false;
}

Kirby::~Kirby() {

}

void Kirby::init(float p_x, float p_y) {
  setX(p_x);
	setY(p_y);

  rightStep_ = sound.loadSound("../data/sounds/step_left.wav");
  leftStep_ = sound.loadSound("../data/sounds/step_right.wav");

  vector_KirbyPainting = createVector(26);
  vector_KirbyWalking = createVector(11);
  vector_Paint = createVector(7);
}

void Kirby::activateAnimation() {
  animation = painting;
}

void Kirby::update(SDL_Renderer* rend, uint32_t dt) {
  static Vector2 paint_pos;
  static float timer = 0.0f;
  static int counter = 0;
  static u16 phase = 0;
  static u16 phase_aux = 0;
  static u16 phase_paint = 1; 
  static bool doitonce = false;

  if(animation == painting || animation == walking) {
    timer += (dt * 0.001f);
    if(timer >= 0.1f){
      timer = 0.0f;
      doitonce = false;
    }
    
  }

  if(animation == painting) {
    if(timer >= 0.0f && timer <= 0.1f) {
      if(phase < 32 && !doitonce) {
        if(phase_aux < 10){
          setY(getY() - 12.5f);
        }
        phase ++;
        phase_aux++;
        doitonce = true;
      }
    }

    if(phase_aux == 20) {
      paint_pos.x = getX();
      paint_pos.y = getY();
    }

    if(phase_aux == 25) {
      phase = 0;
      phase_aux = 0;
      //setY(SCREEN_HEIGHT_* 0.9f);
      animation = walking;
    }
    if(phase == 8) {
      phase_aux = 1;
    }
    //printf("%d\n", phase);
  }

  if(animation == walking) {
    if(timer >= 0.0f && timer <= 0.1f) {
      if(phase < 10 && !doitonce) {
        setX(getX() + 12.5f);
        phase ++;
        if(counter > 1){
          phase_paint ++; 
        }
        doitonce = true;
      }
    }

    if(phase >= 10) {
      phase = 0;
      counter++;
    }
  }

  if(getX() >= SCREEN_WIDTH_ + 100.0f) {
    phase = 0;
    phase_paint = 1;
    counter = 0;
    setY(SCREEN_HEIGHT_* 0.9f);
    setX(SCREEN_WIDTH_* 0.75f);
    animation = noAnimation;
  }
  static bool play_once = false;
  switch(animation) {
    case painting: Sprite::drawSprite(vector_KirbyPainting, phase_aux, getX(), getY(), rend);
                   if(phase_aux == 22) Sprite::drawSprite(vector_Paint, 0, paint_pos.x, paint_pos.y + 50.0f, rend);
                   if(phase_aux == 23 || phase_aux == 24) Sprite::drawSprite(vector_Paint, 1, paint_pos.x, paint_pos.y + 50.0f, rend);

    break;
    case walking: Sprite::drawSprite(vector_KirbyWalking, phase, getX(), getY() + 65.0f, rend);
                  if(!play_once){
                    switch(phase) {
                      case 0: //sound.playSound(rightStep_);
                              play_once = true;
                      break;
                      case 5: //sound.playSound(leftStep_);
                              play_once = true;
                      break;
                    }
                  }
                  play_once = false;
                  if(phase_paint < 6) {
                    if(counter > 1){
                      Sprite::drawSprite(vector_Paint, phase_paint, paint_pos.x, paint_pos.y + 50.0f + (phase * 1.75f), rend);
                    }else{
                      Sprite::drawSprite(vector_Paint, phase_paint, paint_pos.x, paint_pos.y + 50.0f, rend);
                    }
                  }else {
                    finish = true;
                  }
                  
    break;
  }


}

void Kirby::free() {

  Mix_FreeChunk(rightStep_);
  Mix_FreeChunk(leftStep_);

  ReleaseSprites(vector_Paint);
  ReleaseSprites(vector_KirbyWalking);
  ReleaseSprites(vector_KirbyPainting);

  textures.releaseTextures(vector_Paint);
  textures.releaseTextures(vector_KirbyWalking);
  textures.releaseTextures(vector_KirbyPainting);

  releaseVector(vector_Paint);
  releaseVector(vector_KirbyWalking);
  releaseVector(vector_KirbyPainting);
}

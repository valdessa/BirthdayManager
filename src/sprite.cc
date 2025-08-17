/**
 * @file   sprite.cc
 * @brief  sprite file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */

#include "sprite.h"

Sprite::Sprite() {
  if (IMG_Init(IMG_INIT_PNG) == 0) {
    std::cout << "Error SDL2_image Initialization";
  }
}

void Sprite::createSprite(Vector* vector, const char* path_rute[], SDL_Renderer* rend) {
  u16 length = vector->ops_->capacity(vector) - 1;
  for (u16 i = 0; i < length; ++i) {
    Sprite* new_data = (Sprite*) MM->malloc(sizeof(Sprite));
    new_data->src = IMG_Load(path_rute[i]);
    if (nullptr == new_data->src) {
      std::cout << "Error loading image: " << IMG_GetError();
    return;
    }
    new_data->texture = SDL_CreateTextureFromSurface(rend, new_data->src);
    SDL_FreeSurface(new_data->src);
    if (nullptr == new_data->texture) {
      std::cout << "Error creating texture";
    return;
    }
    vector->ops_->insertLast(vector, (void*) new_data, sizeof(Sprite));
  };
}

void Sprite::drawSprite(Vector* vector, u16 sprite_number, float pos_x, float pos_y, SDL_Renderer* rend) {
  if (nullptr == vector) {
    return;
  }
  MyTexture texture_aux;
  Sprite* tmp_data = (Sprite*) vector->ops_->at(vector, sprite_number);
  SDL_Rect source;
  source.x = 0;
  source.y = 0;
  SDL_QueryTexture(tmp_data->texture, NULL, NULL, &source.w, &source.h);
  SDL_Rect dst;
  dst.x = (int)pos_x;
  dst.y = (int)pos_y;
  dst.w = (source.w * (int)scale().x);
  dst.h = (source.h * (int)scale().y);
  SDL_RenderCopy(rend, tmp_data->texture, &source, &dst);
  width_ = texture_aux.setWidth(tmp_data->texture, width_);
  height_ = texture_aux.setHeight(tmp_data->texture, height_);
  //printf("X: %d  Y: %d\n", getWidth(), getHeight());
}

void Sprite::ReleaseSprites(Vector* vector) {
  if (nullptr == vector) {
    printf("ERROR RELEASING THE SPRITES\n");
    return;
  }

  u16 length = vector->ops_->length(vector);
  for (u16 i = 0; i < length; ++i) {
    Sprite* tmp_data = (Sprite*) vector->ops_->at(vector, i);
    if(nullptr == tmp_data->src){
      SDL_FreeSurface(tmp_data->src);
    }
  }
}

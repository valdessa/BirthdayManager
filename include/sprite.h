/**
 * @file   sprite.h
 * @brief  sprite header file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */

#ifndef __SPRITE_H__
#define __SPRITE_H__ 1

#include <iostream>
#include "window.h"
#include "mytexture.h"


class Sprite : public Entity {
 public:

/** @brief Sprite Constructor
 *
*/
  Sprite();

/** @brief Creates a Sprite
 *
 * Creates a Sprite from ref
 *
 * @param *vector where the sprite will be saved
 * @param *path_route the path route of the sprite
 * @param *rend renderer from SDL_Renderer
*/
  void createSprite(Vector* vector, const char* path_route[], SDL_Renderer* rend);

/** @brief Draws a Sprite
 *
 * @param *vector where the sprite is stored
 * @param sprite_number Sprite position on the vector that will be drawn
 * @param pos_x position X of the sprite that will be drawn
 * @param pos_y position Y of the sprite that will be drawn
 * @param *rend renderer from SDL_Renderer
*/
  void drawSprite(Vector* vector, u16 sprite_number, float pos_x, float pos_y, SDL_Renderer* rend);

/** @brief Release a sprite from memory
 *
 * @param *vector where the sprite is stored
*/
  void ReleaseSprites(Vector* vector);
  SDL_Surface* src;
  SDL_Texture* texture; //TODO: from class texture.h
};
#endif

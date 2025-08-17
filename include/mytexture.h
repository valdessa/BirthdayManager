/**
 * @file   texture.h
 * @brief  texture header file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */

#ifndef __MYTEXTURE_H__
#define __MYTEXTURE_H__ 1

#include <SDL.h>
#include <SDL_ttf.h>

#include "entity.h"

class MyTexture {
 public:
/** @brief Texture Constructor
 *
*/
  MyTexture();

/** @brief Load Texture
 *
 * Loads and creates a Texture from a surface
 *
 * @param *rend from SDL_Renderer
 * @param *surface from SDL_Surface
 *
 * @return the new texture created
*/
  SDL_Texture* loadTexture(SDL_Renderer* rend, SDL_Surface* surface);

/** @brief Load Texture
 *
 * Loads and creates a Texture from a path
 *
 * @param *p_filePath path route of the image
 * @param *surface from SDL_Surface
 *
 * @return the new texture created
*/
	SDL_Texture* loadTexture(const char* p_filePath, SDL_Renderer* rend);

/** @brief set a Width to the Texture
 *
 * @param *tex from SDL_Texture
 * @param new_width the new Width that will be applied to the texture
 *
 * @return the new Width
*/
  int setWidth(SDL_Texture* tex, int new_width);

/** @brief set a Height to the Texture
 *
 * @param *tex from SDL_Texture
 * @param new_height the new Height that will be applied to the texture
 *
 * @return the new Height
*/
  int setHeight(SDL_Texture* tex, int new_height);

/** @brief render Text
 *
 * Creates the surface and texture where the text will be placed
 *
 * @param *p_text text that will be shown
 * @param **message texture where the text will be placed
 * @param *font used from TTF_Font
 * @param textColor color of the the text
 * @param *rend from SDL_Renderer
*/
  void renderText(const char* p_text, SDL_Texture** message, TTF_Font* font, SDL_Color textColor, SDL_Renderer* rend);

/** @brief draw Text
 *
 * @param pos_x position X where the text will be drawn
 * @param pos_y position Y where the text will be drawn
 * @param *text texture where the text is allocated
 * @param *rend from SDL_Renderer
*/
  void drawText(float pos_x, float pos_y, SDL_Texture* text, SDL_Renderer* rend);

/** @brief Render a texture
 *
 * @param p_x position X where the texture will be drawn
 * @param p_y position Y where the texture will be drawn
 * @param *p_tex texture that will be rendered
 * @param *rend from SDL_Renderer
*/
  void render(float p_x, float p_y, SDL_Texture* p_tex, SDL_Renderer* rend);

/** @brief Release a texture from a vector
 *
 * @param *vector from where the texture will be released
*/
  void releaseTextures(Vector* vector);

/** @brief Release a texture
 *
 * @param *texture the texture that is going to be released
*/
  void releaseTextures(SDL_Texture* texture);

  int getWidth(SDL_Texture* tex);
  int getHeight(SDL_Texture* tex);

  SDL_Texture* myTexture;
  SDL_Color white  = { 255, 255, 255 };
  SDL_Color black  = { 0,   0,   0   };
  SDL_Color gray   = { 128, 128, 128 }; 
  SDL_Color red    = { 255, 0,   0   };
  SDL_Color green  = { 0,   255, 0   };
  SDL_Color blue   = { 0,   0,   255 };
  SDL_Color yellow = { 255, 255, 0   };
  SDL_Color orange = { 255, 128, 0   };
  SDL_Color cyan   = { 0,   255, 255 };
  SDL_Color pink   = { 255, 0,   255 };
};

#endif

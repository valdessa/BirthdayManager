/**
 * @file   window.h
 * @brief  window header file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */

#ifndef __WINDOW_H__
#define __WINDOW_H__ 1

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "vector_4.h"
#include "entity.h"

const int SCREEN_WIDTH_ = 1400;
const int SCREEN_HEIGHT_ = 800;

class RenderWindow : public Entity {
 public:

 /** @brief Window constructor
  *
 */
	RenderWindow();

/** @brief Create a window
 *
 * Creates a window with a specific size
 *
 * @param *p_title name of the Window
 * @param p_w p_h Width and Height of the new Window
*/
	void create(const char* p_title, int p_w, int p_h);

/** @brief Create a window
 *
 * Creates a window
 *
 * @param *p_title name of the Window
*/
	void create(const char* p_title);

/** @brief Create a Texture
 *
 * @param *p_filePath path route of the texture
*/
	SDL_Texture* loadTexture(const char* p_filePath);

/** @brief Clears and apply a color to the window's background
 *
 * @param color the new color of the window's background
*/
	void clear(Vector4 color);

  void setWindowIcon(const char* icon_path);

  void setRenderColor(Vector4 color);

/** @brief Render a texture
 *
 * @param p_x position X where the texture will be drawn
 * @param p_y position Y where the texture will be drawn
 * @param *p_tex texture that will be rendered
*/
	void render(float p_x, float p_y, SDL_Texture* p_tex);

/** @brief Render a texture
 *
 * @param *p_tex texture that will be rendered
*/
	void render(SDL_Texture* p_tex);

/** @brief render Text
 *
 * Creates the surface and texture where the text will be placed
 *
 * @param p_x position X where the text will be drawn
 * @param p_y position Y where the text will be drawn
 * @param *p_text texture where the text will be placed
 * @param *font used from TTF_Font
 * @param textColor color of the the text
*/
	void render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);

/** @brief render Text at the middle of the Screen
 *
 * Creates the surface and texture where the text will be placed and puts it at the middle of the screen
 *
 * @param p_x position X where the text will be drawn
 * @param p_y position Y where the text will be drawn
 * @param *p_text texture where the text will be placed
 * @param *font used from TTF_Font
 * @param textColor color of the the text
*/
	void renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);

/** @brief Updates the delta time
 *
*/
  void updateTime();

/** @brief Display the renderer
 *
*/
	void display();

/** @brief Destroy the renderer and the window
 *
*/
	void destroy();

  const int SCREEN_WIDTH = SCREEN_WIDTH_;
  const int SCREEN_HEIGHT = SCREEN_HEIGHT_;
	uint32_t delta_time_;
  SDL_Renderer* renderer_;
  SDL_Window* window_;
 private:
	 uint32_t last_tick_time_;
};

#endif

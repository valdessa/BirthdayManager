/**
 * @file   my_imgui.h
 * @brief  my_imgui header file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */

#ifndef __MYIMGUI_H__
#define __MYIMGUI_H__ 1

#define MAKECODE(p) ((((p)[0])*0x01000000) \
                   + (((p)[1])*0x00010000) \
                   + (((p)[2])*0x00000100) \
                   +  ((p)[3]) )

#include <SDL.h>
#include <SDL_image.h>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#include "window.h"

class MyImGui : public RenderWindow{
 public:

/** @brief ImGui Constructor
 *
*/
	MyImGui();

/** @brief initializes ImGui and its variables
 *
 * @param window from SDL_CreateWindow
*/
  void init(RenderWindow window);

/** @brief updates ImGui
 *
 * @param window from SDL_CreateWindow
*/
  void update(RenderWindow window);

/** @brief sets ImGui's next window size and position
 *
 * @param size_x size_y size of the next ImGui's window
 * @param pos_x pos_y position of the next ImGui's window
*/
  void setWindow(float size_x, float size_y, float pos_x, float pos_y);



  void setWindowStatic(float size_x, float size_y, float pos_x, float pos_y);

/** @brief create a new ImGui window
 *
 * @param *name name of the new ImGui window
 * @param resize if the new window can be resized or not
 * @param move if the new window can be moved or not
*/
  void newWindow(const char *name, bool resize, bool move);

  void MyStyleSettings();

  void SetButtonColor(const char *color);

  void SetInputColor(const char *color);

  void SetHeaderColor(const char *color);

  void addSeparator(int cicles);

  void addSpace(int cicles);

  void setPositionX(float pos);

  void end();



/** @brief render the ImGui window
 *
*/
  void render();

/** @brief destroy the ImGui window
 *
*/
  void destroy();
};

#endif

/**
 * @file   window.cc
 * @brief  window file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "window.h"

RenderWindow::RenderWindow(){
	delta_time_ = 0;
	last_tick_time_ = 0;
}

void RenderWindow::create(const char* p_title, int p_w, int p_h) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		std::cout << "Error SDL2 Initialization : " << SDL_GetError();
	}

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE  | SDL_WINDOW_ALLOW_HIGHDPI);
	window_ = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_w, p_h, window_flags);

	if (window_ == NULL)
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	if (renderer_ == NULL) {
		std::cout << "Error renderer creation";
	}
}

void RenderWindow::create(const char* p_title) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		std::cout << "Error SDL2 Initialization : " << SDL_GetError();
	}

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
	window_ = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);

	if (window_ == NULL)
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	if (renderer_ == NULL) {
		std::cout << "Error renderer creation";
	}
}

void RenderWindow::setWindowIcon(const char* icon_path) {
	SDL_Surface* icon = IMG_Load(icon_path);
	SDL_SetWindowIcon(window_, icon);
	SDL_FreeSurface(icon);
}

void RenderWindow::setRenderColor(Vector4 color) {
	SDL_SetRenderDrawColor(renderer_, (Uint8)color.x, (Uint8)color.y, (Uint8)color.z, (Uint8)color.w);
}

void RenderWindow::clear(Vector4 color) {
	SDL_SetRenderDrawColor(renderer_, (Uint8)color.x, (Uint8)color.y, (Uint8)color.z, (Uint8)color.w);
	SDL_RenderClear(renderer_);
}

void RenderWindow::updateTime() {
    uint32_t tick_time_ = SDL_GetTicks();
    delta_time_ = tick_time_ - last_tick_time_;
    last_tick_time_ = tick_time_;
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer_);
}

void RenderWindow::destroy() {
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

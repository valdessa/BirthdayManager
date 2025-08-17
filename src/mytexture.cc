/**
 * @file   texture.cc
 * @brief  texture file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */

#include "mytexture.h"

MyTexture::MyTexture() {

}

SDL_Texture* MyTexture::loadTexture(SDL_Renderer* rend, SDL_Surface* surface) {
  if(nullptr == surface){
    printf("ERROR LOADING THE SURFACE\n");
  }
	SDL_Texture* new_texture = NULL;
	new_texture =	SDL_CreateTextureFromSurface(rend, surface);

	if (new_texture == NULL)
		printf("Failed to load texture. Error: %s\n", SDL_GetError());

	return new_texture;
}

SDL_Texture* MyTexture::loadTexture(const char* p_filePath, SDL_Renderer* rend) {
	SDL_Texture* new_texture = NULL;
	new_texture = IMG_LoadTexture(rend, p_filePath);

	if (new_texture == NULL)
		printf("Failed to load texture. Error: %s\n", SDL_GetError());

	return new_texture;
}

int MyTexture::setWidth(SDL_Texture* tex, int new_width) {
	SDL_QueryTexture(tex, NULL, NULL, &new_width, NULL);
	return new_width;
}

int MyTexture::setHeight(SDL_Texture* tex, int new_height) {
	SDL_QueryTexture(tex, NULL, NULL, NULL, &new_height);
	return new_height;
}

int MyTexture::getWidth(SDL_Texture* tex) {
  int new_width;
	SDL_QueryTexture(tex, NULL, NULL, &new_width, NULL);
	return new_width;
}

int MyTexture::getHeight(SDL_Texture* tex) {
  int new_height;
	SDL_QueryTexture(tex, NULL, NULL, NULL, &new_height);
	return new_height;
}

void MyTexture::renderText(const char* p_text, SDL_Texture** message, TTF_Font* font, SDL_Color textColor, SDL_Renderer* rend) {
	SDL_Surface* temp_surface = TTF_RenderText_Solid(font, p_text, textColor);
	*message = SDL_CreateTextureFromSurface(rend, temp_surface);
  if (nullptr == message) {
    printf("ERROR CREATING THE TEXTURE\n");
    return;
  }
	SDL_FreeSurface(temp_surface); temp_surface = nullptr;
}

void MyTexture::drawText(float pos_x, float pos_y, SDL_Texture* text, SDL_Renderer* rend) {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(text, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = (int)pos_x;
	dst.y = (int)pos_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(rend, text, &src, &dst);
}

void MyTexture::render(float p_x, float p_y, SDL_Texture* p_tex, SDL_Renderer* rend) {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = (int)p_x;
	dst.y = (int)p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(rend, p_tex, &src, &dst);
}

void MyTexture::releaseTextures(Vector* vector) {
  if (nullptr == vector) {
    printf("ERROR RELEASING THE TEXTURE\n");
    return;
  }

  u16 length = vector->ops_->length(vector);
  for (u16 i = 0; i < length; ++i) {
    MyTexture* tmp_data = (MyTexture*) vector->ops_->at(vector, i);
    SDL_DestroyTexture(tmp_data->myTexture);
  }
}

void MyTexture::releaseTextures(SDL_Texture* old_texture) {
  if (nullptr == old_texture) {
    printf("ERROR RELEASING THE TEXTURE\n");
    return;
  }
  SDL_DestroyTexture(old_texture);
	old_texture = nullptr;
}

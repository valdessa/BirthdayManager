/**
 * @file   entity.h
 * @brief  entity header file
 *
 * @author Mario Galán (galanso) "galanso@esat-alumni.com"
 * @date   December 2021
 */

#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>

#include "vector_2.h"
#include "vector_4.h"

extern "C" {
#include "./ADT/adt_memory_node.h"
#include "./ADT/adt_vector.h"
#include "./EDK_MemoryManager/edk_platform_types.h"
#include "./EDK_MemoryManager/edk_memory_manager.h"
}

class Entity {
public:
	Entity();
	Entity(const Entity& copy);
	Entity(float p_x, float p_y);

	virtual ~Entity();
	void init();
	void init(int scene, float scale, float angle, Vector2 position);
	//Our Vector
	Vector* createVector(u16 size);
	void releaseVector(Vector* vector);
	//Setters
	void set_position(const Vector2 pos);
	void setX(const float pos_x);
	void setY(const float pos_y);
	void set_rotation(const float rot);
	void set_scale(const Vector2 sca);
	void setWidth(SDL_Texture* tex, int new_width);
	void setHeight(SDL_Texture* tex, int new_height);
	//Getters
	Vector2 position() const;
	float getX() const;
	float getY() const;
	float rotation() const;
	Vector2 scale() const;
	int getWidth();
	int getHeight();

//--------------------------------------------------------------------------

	int scene_;



 protected:
	int height_;
	int width_;
	Vector2 position_;
	float rotation_;
	Vector2 scale_;

};

#endif

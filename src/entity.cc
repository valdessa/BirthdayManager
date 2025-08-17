/**
 * @file   entity.cc
 * @brief  entity file
 *
 * @author Mario Galán (galanso) "galanso@esat-alumni.com"
 * @collab Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>

#include "entity.h"

Entity::Entity() {
	scene_ = 0;

	position_.x = 0.0f;
	position_.y = 0.0f;

	rotation_ = 0.0f;

	scale_ = 10.f;
}

Entity::Entity(float p_x, float p_y) {
	position_.x = p_x;
	position_.y = p_y;
}

Entity::Entity(const Entity& copy){
	scene_ = copy.scene_;
	scale_ = copy.scale_;
	rotation_ = copy.rotation_;
	position_.x = copy.position_.x;
	position_.y = copy.position_.y;
}

Entity::~Entity() {}

void Entity::init() {
	scene_ = 0;

	position_.x = 0.0f;
	position_.y = 0.0f;

	rotation_ = 0.0f;

	scale_ = 10.f;
}

void Entity::init(int scene, float scale, float angle, Vector2 position) {
	scene_ = scene;
	scale_ = scale;
	rotation_ = angle;
	position_.x = position.x;
	position_.y = position.y;
}

Vector* Entity::createVector(u16 size) {
  Vector* vector = (Vector*) VECTOR_create(size);
  return vector;
}

void Entity::releaseVector(Vector* vector){
	if(nullptr == vector){
		printf("ERROR RELEASING THE VECTOR\n");
		return;
	}

	vector->ops_->destroy(vector);
	vector = nullptr;
}

void Entity::set_position(const Vector2 pos) {
	position_ = pos;
}

void Entity::setX(const float pos_x){
	position_.x = pos_x;
}

void Entity::setY(const float pos_y){
	position_.y = pos_y;
}

void Entity::set_rotation(const float rot) {
	rotation_ = rot;
}

void Entity::set_scale(const Vector2 sca) {
	scale_ = sca;
}

void Entity::setWidth(SDL_Texture* tex, int new_width) {
	SDL_QueryTexture(tex, NULL, NULL, &new_width, NULL);
	//return width_;
}

void Entity::setHeight(SDL_Texture* tex, int new_height) {
	SDL_QueryTexture(tex, NULL, NULL, NULL, &new_height);
	//return height_;
}

Vector2 Entity::position() const {
	return position_;
}

float Entity::getX() const {
	return position_.x;
}

float Entity::getY() const {
	return position_.y;
}

float Entity::rotation() const {
	return rotation_;
}

Vector2 Entity::scale() const {
	return scale_;
}

int Entity::getWidth() {
	return width_;
}

int Entity::getHeight() {
	return height_;
}

/**
 * @file   sound.cc
 * @brief  sound file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */

#include "sound.h"

Sound::Sound() {

}

Sound::~Sound() {

}

void Sound::initSound() {
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

Mix_Chunk* Sound::loadSound(char* p_filePath) {
  return (Mix_LoadWAV(p_filePath));
}

void Sound::playSound(Mix_Chunk* sound){
  Mix_PlayChannel(-1, sound, 0);
}

void Sound::destroySound(){
    Mix_CloseAudio();
}

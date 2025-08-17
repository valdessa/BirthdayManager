/**
 * @file   sound.h
 * @brief  sound header file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */

#ifndef __SOUND_H__
#define __SOUND_H__ 1

#include <iostream>
#include "window.h"
#include <SDL_mixer.h>


class Sound {
 public:

/** @brief Sound Constructor
*
*/
  Sound();

/** @brief Sound Destructor
 *
*/
  ~Sound();

/** @brief initialize sound library
 *
*/
  void initSound();

/** @brief load sound
 *
 * @param p_filePath path of the sound
*/
  Mix_Chunk* loadSound(char* p_filePath);

/** @brief Play sound
 *
 * @param *sound the sound that is going to be played
*/
  void playSound(Mix_Chunk* sound);

/** @brief Destroy sound
 *
*/
  void destroySound();
};
#endif

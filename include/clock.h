/**
 * @file   clock.h
 * @brief  clock header file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */
#ifndef __CLOCK_H__
#define __CLOCK_H__ 1

#include <SDL.h>
#include <SDL_image.h>
#include <time.h>

#include "entity.h"
#include "window.h"
#include "my_imgui.h"
#include "sound.h"
#include "kirby.h"
#include "mytexture.h"

struct databaseinfo; //From Database .h

const float PI = 3.14159265358979f;
const float degtorad = (PI * 2.0f) / 360.0f;

static const int DaysInMon[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static const char *monthsItems[]{"Select a Month","January", "February", "March", "April", "May", "June", 
                                 "July", "August", "September", "October", "November", "December"};
static const char *daysItems[]{"Select a Day", "01", "02", "03", "04", "05", "06", "07", "08", "09", 
                               "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", 
                               "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"};

struct SomeData {
  int number;
};

class Clock : public Entity{
 public:
  //CONSTRUCTORS
  Clock();
  Clock(float pos_x, float pos_y);

  //INIT THINGS
  void InitMonthDayNames();
  void initPointers();
  void init();


  //UPDATE 
  void updateTimerClock();

  //SOUND
  void clockSound();

  //DRAW HOURS AND DATE NUMBERS
  void digitalHour(RenderWindow *win);
  void digitalDate(RenderWindow *win);
  void numberAroundClock(RenderWindow *win);

  //DRAW CLOCK THINGS 
  void plotLineAngle(SDL_Renderer *rend,  double degrees, double magnitude);
  void drawCircle(SDL_Renderer *rend, int steps, double radius);
  void drawHours(SDL_Renderer *rend, double radius1, double radius2);

  //DRAW CLOCK AND ITS THINGS
  void draw(RenderWindow *win); 


  //IMGUI WINDOW CLOCK SETTINGS 
  void imguiClockWindow();

  //GETTERS
  int getHour();
  int getMinute();
  int getSecond();
  int getDayNumber();
  int getMonthNumber();
  int getYearNumber();
  char* getHourString();
  char* getMinuteString();
  char* getSecondString();
  char* getYear();
  char* getMonth();
  char* getDay();
  char* getMonthName();
  char* getDayName();
  char* getTotalDate();
  char* getActualTime();

  //GETTERS BIRTHDAY FROM DATABASE:
  int getTotalAge(databaseinfo *current_user, int user, const char* date);
  std::string getWeekDay(databaseinfo *current_user, int user);
  float getTotalMonthsLived(databaseinfo *current_user, int user);
  int getTotalDaysLived(databaseinfo *current_user, int user);
  int getTotalHoursLived(int days_lived);
  int getTotalMinutesLived(int hours_lived);
  unsigned long getTotalSecondsLived(int minutes_lived);
  int getNextBirthday(databaseinfo *current_user, int user, const char* date);
  int getTotalDaysUntilBirthday(databaseinfo *current_user, int user);
  int getTotalHoursUntilBirthday(int days_left);
  int getTotalMinutesUntilBirthday(int hours_left);
  int getTotalSecondsUntilBirthday(int minutes_left);
  std::string getZodiacName(databaseinfo *current_user, int user);
  std::string Clock::getNextWeekDayOfBirthday(databaseinfo *current_user, int user);
  void ShowBirthdaysName(Kirby *act_kirby, RenderWindow *win);

  //FREE POINTERS
  void freeDatePointers();
  void freePointers();

  RenderWindow window;
     
  bool mute;
  bool showDigitalHour_;
  bool showDate_;

  Mix_Chunk *clock1_;
  Mix_Chunk *clock2_;
  Sound sound;
  TTF_Font* font16;
  TTF_Font* font20;
  TTF_Font* font20_outline;
  SDL_Texture* hours_[13] = {nullptr};
  Vector* hour_vector_;
  MyImGui my_imgui;
  MyTexture my_texture;

 protected:
  //Clock Time Variables;
  int hour;
  int minute;
  int second;
  char year_[5];
  char **months, **days, actualTime_[26];

 private:
  time_t t;
  struct tm tm;
};

#endif

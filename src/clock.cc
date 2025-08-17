/**
 * @file   clock.cc
 * @brief  clock file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */

#include "clock.h"
#include "database.h"

//CONSTRUCTORS
Clock::Clock() {
  t = time(NULL);
  tm = *localtime(&t);
  mute = true;
  showDigitalHour_ = true;
  showDate_ = true;
}

Clock::Clock(float pos_x, float pos_y) {
  setX(pos_x);
	setY(pos_y);
  t = time(NULL);
  tm = *localtime(&t);
  mute = true;
  showDigitalHour_ = true;
  showDate_ = true;
}

//INIT
void Clock::InitMonthDayNames() {
  *(months+0)="January\0";
	*(months+1)="February\0";
	*(months+2)="March\0";
	*(months+3)="April\0";
	*(months+4)="May\0";
	*(months+5)="June\0";
	*(months+6)="July\0";
	*(months+7)="August\0";
	*(months+8)="September\0";
	*(months+9)="October\0";
	*(months+10)="November\0";
	*(months+11)="December\0";

	*(days+0)="Sunday\0";
	*(days+1)="Monday\0";
	*(days+2)="Tuesday\0";
	*(days+3)="Wednesday\0";
	*(days+4)="Thursday\0";
	*(days+5)="Friday\0";
	*(days+6)="Saturday\0";
}

void Clock::initPointers() {
  months = (char**)malloc(12 * sizeof(months));
  days = (char**)malloc(7 * sizeof(days));
  InitMonthDayNames();
}

void Clock::init() {
  initPointers();
  sound.initSound();
  font16 = TTF_OpenFont("../data/fonts/cocogoose.ttf", 16);
  font20 = TTF_OpenFont("../data/fonts/cocogoose.ttf", 20);
  font20_outline = TTF_OpenFont("../data/fonts/cocogoose.ttf", 20);
  TTF_SetFontOutline(font20_outline, 2);
  clock1_ = sound.loadSound("../data/sounds/clock1.wav");
  clock2_ = sound.loadSound("../data/sounds/clock2.wav");
  hour_vector_ = createVector(13);
  for(u16 i = 0; i < 13; i++) {
    SomeData* new_data = (SomeData*) MM->malloc(sizeof(SomeData));
    new_data->number = i;
    hour_vector_->ops_->insertLast(hour_vector_, (void*) new_data, sizeof(SomeData));
  }
  printf("Week Day ....: %s\n", getDayName());
	printf("DD ..........: %s\n", getDay());
	printf("Year Month ..: %s\n", getMonthName());
  printf("MM ..........: %s\n", getMonth());
	printf("YYYY ........: %s\n", getYear()); 
  printf("Date ........: %s\n", getTotalDate());
}

//UPDATE 
void Clock::updateTimerClock() {
    t = time(NULL);
    tm = *localtime(&t);
  	hour = tm.tm_hour;
  	minute = tm.tm_min;
  	second = tm.tm_sec;
    asctime_s(actualTime_, 26, &tm);
}

//SOUND
void Clock::clockSound() {
  static int passed1 = getSecond();
  static bool firstTime = true;

  if(passed1 ==  getSecond() && !firstTime){
    static int sound_stage = 0;
    switch (sound_stage) {
      case 0: if(!mute)sound.playSound(clock1_); sound_stage = 1; break;
      case 1: if(!mute)sound.playSound(clock2_); sound_stage = 0; break;
    }
    passed1 ++;
  }

  if(passed1 >= 60) passed1 = 0;
  firstTime = false;
}

//DRAW HOURS AND DATE NUMBERS
void Clock::digitalHour(RenderWindow *win) {
  char finalHour_buffer[33] = "\0";
  char hour_buffer[33];
  sprintf(hour_buffer, "%02d", getHour());
  char minute_buffer[33];
  sprintf(minute_buffer, "%02d", getMinute());
  char second_buffer[33];
  sprintf(second_buffer, "%02d", getSecond());
  strcat(finalHour_buffer, hour_buffer);
  strcat(finalHour_buffer, " : ");
  strcat(finalHour_buffer, minute_buffer);
  strcat(finalHour_buffer, " : ");
  strcat(finalHour_buffer, second_buffer);

  if(showDigitalHour_) {
    SDL_Texture* digitalHour_ = nullptr;
    SDL_Texture* digitalHourOutline_ = nullptr;
    my_texture.renderText(finalHour_buffer, &digitalHourOutline_, font20_outline, my_texture.blue, win->renderer_);
    my_texture.renderText(finalHour_buffer, &digitalHour_, font20, my_texture.white, win->renderer_);
    int text_width = my_texture.getWidth(digitalHour_);
    my_texture.drawText((getX() - (text_width * 0.5f)) -2.0f, getY() + 48.0f, digitalHourOutline_, win->renderer_);
    my_texture.drawText(getX() - (text_width * 0.5f), getY() + 50.0f, digitalHour_, win->renderer_);
    memset(finalHour_buffer, '\0', sizeof(char) * 33);
    my_texture.releaseTextures(digitalHourOutline_);
    my_texture.releaseTextures(digitalHour_);
  }
}

void Clock::digitalDate(RenderWindow *win) {
  SDL_Texture *digitalDate = nullptr;
  SDL_Texture *digitalDay = nullptr;

  if(showDate_) {
    my_texture.renderText(getDayName(), &digitalDay, font16, my_texture.cyan, win->renderer_);
    my_texture.renderText(getTotalDate(), &digitalDate, font16, my_texture.gray, win->renderer_);
    int text_width = my_texture.getWidth(digitalDay);
    int text_width1 = my_texture.getWidth(digitalDate);
    my_texture.drawText(getX() - (text_width * 0.5f), getY() -245.0f, digitalDay, win->renderer_);
    my_texture.drawText(getX() - (text_width1 * 0.5f), getY() -225.0f, digitalDate, win->renderer_);
    my_texture.releaseTextures(digitalDay);
    my_texture.releaseTextures(digitalDate);
  }
}

void Clock::numberAroundClock(RenderWindow *win) {
  static bool done = false;
  static u16 length = hour_vector_->ops_->length(hour_vector_);
  static char text[13][33];
  for(u16 i = 0; i < length ; i++) {
    SomeData* tmp_data = (SomeData*) hour_vector_->ops_->at(hour_vector_, i);
    sprintf(text[i], "%zu", tmp_data->number);
  }
  for (int i = 30; i < 390; i+= 30) {
    int aux_number;
    aux_number = i/30;
    double endx = 175 * -cos (i * degtorad + 32.985f);
    double endy = 175 * -sin (i * degtorad + 32.985f);


    if(!done) {
      my_texture.renderText(text[aux_number], &hours_[aux_number], font16, my_texture.green, win->renderer_);
    }


    float text_width = (float)my_texture.getWidth(hours_[aux_number]);
    float text_height = (float)my_texture.getHeight(hours_[aux_number]);
    my_texture.drawText((float)endx + (getX() - (text_width * 0.5f)), (float)endy + (getY() - (text_height * 0.45f)), hours_[aux_number], win->renderer_);

  }
  done = true;

  //printf("\n");
}

void Clock::ShowBirthdaysName(Kirby *act_kirby, RenderWindow *win) { 
  static int counter = 0;
  if(act_kirby->animation == painting) {
    mute = false;
  }

  if(act_kirby->finish) {
    SDL_Texture *name = nullptr;
    SDL_Texture *title = nullptr;
    my_texture.renderText(act_kirby->todaysBirthday, &name, font16, my_texture.red, win->renderer_);
    my_texture.renderText("TODAY'S BIRTHDAY:", &title, font16, my_texture.red, win->renderer_);
    int text_width = my_texture.getWidth(name);
    int text_width2 = my_texture.getWidth(title);
    my_texture.drawText(SCREEN_WIDTH_ * 0.8f - (text_width * 0.5f), SCREEN_HEIGHT_ * 0.8f, name, win->renderer_);
    my_texture.drawText(SCREEN_WIDTH_ * 0.8f - (text_width2 * 0.5f), SCREEN_HEIGHT_ * 0.75f, title, win->renderer_);
    my_texture.releaseTextures(name);
    my_texture.releaseTextures(title);
    counter++;
  }

  if(counter >= 2500) {
    act_kirby->finish = false;
    act_kirby->animation = noAnimation;
    counter = 0;
  }
}

//DRAW CLOCK THINGS
void Clock::drawCircle(SDL_Renderer *rend, int steps, double radius) {

	int i;
	double angleDelta = (steps >= 3) ? 360.0/steps : 120;

	for (i = 0; i < steps; i++) {

		double endx = radius * cos (i * angleDelta * degtorad);
		double endy = radius * sin (i * angleDelta * degtorad);

		double endxNext = radius * cos ((i + 1) * angleDelta * degtorad);
		double endyNext = radius * sin ((i + 1) * angleDelta * degtorad);

		SDL_RenderDrawLineF(rend, (float)endx + getX(), (float)endy + getY(), (float)endxNext + getX(), (float)endyNext + getY());
	}

}

void Clock::drawHours(SDL_Renderer *rend, double radius1, double radius2) {

	int i;

	for (i = 0; i < 360; i+= 6) {
		double endx = radius1 * cos (i * degtorad);
		double endy = radius1 * sin (i * degtorad);
    double endx2;
    double endy2;
    if(i % 30 == 0) {
      endx2 = radius2 * 1.05f * cos (i * degtorad);
      endy2 = radius2 * 1.05f * sin (i * degtorad);
    }else {
      endx2 = radius2 * cos (i * degtorad);
      endy2 = radius2 * sin (i * degtorad);
    }

		SDL_RenderDrawLineF(rend, (float)endx + getX(), (float)endy + getY(), (float)endx2 + getX(), (float)endy2 + getY());
	}

}

void Clock::plotLineAngle(SDL_Renderer *rend, double degrees, double magnitude) {

	double w = magnitude * cos (degrees * degtorad);
  double h = magnitude * sin (degrees * degtorad);
  SDL_RenderDrawLineF(rend, getX(), getY(), getX()+(int)w, getY()+(int)h);

}

void Clock::draw(RenderWindow *win) {
  /*Draw Digital Hour and Hour numbers*/
  digitalHour(win);
  digitalDate(win);
  numberAroundClock(win);

  /*Draw clock wireframe*/
  win->setRenderColor(Vector4(0, 136, 255, 255));
  drawCircle(win->renderer_, 60, 190);
  drawCircle(win->renderer_, 40, 140);

  /*Draw hours*/
  win->setRenderColor(Vector4(0, 255, 0, 255));
  drawHours(win->renderer_, 145, 155);

  /*Draw hour hand*/
  win->setRenderColor(Vector4(255, 255, 255, 255));
  plotLineAngle(win->renderer_, hour * 30 - 90, 120);

  /*Draw minute hand*/
  win->setRenderColor(Vector4(255, 255, 0, 255));         
  plotLineAngle(win->renderer_, minute * 6 - 90, 150);

  /*Draw second hand*/
  win->setRenderColor(Vector4(255, 0, 0, 255));
  plotLineAngle(win->renderer_, second * 6 - 90, 165);
}

//IMGUI WINDOW CLOCK SETTINGS 
void Clock::imguiClockWindow() {
  static float pos_x = getX();
  static float pos_y = getY();
  
  my_imgui.setPositionX(65.0f);
  ImGui::SliderFloat("", &pos_x, 0.0f, (float)window.SCREEN_WIDTH, "PositionX = %.3f");
  my_imgui.setPositionX(65.0f);
  ImGui::SliderFloat(" ", &pos_y, 0.0f, (float)window.SCREEN_HEIGHT, "PositionY = %.3f");
  
  my_imgui.addSpace(1);

  my_imgui.setPositionX(80.0f);
  my_imgui.SetButtonColor("green");
  if(ImGui::Button("RESET CLOCK POSITION", ImVec2(200.0f, 20.0f))){
    pos_x = window.SCREEN_WIDTH * 0.8f;
    pos_y = window.SCREEN_HEIGHT * 0.35f;
  }
  my_imgui.SetButtonColor("blue");
  my_imgui.addSpace(1);

  my_imgui.setPositionX(60.0f);
  ImGui::Checkbox("SHOW DIGITAL HOUR", &showDigitalHour_); ImGui::SameLine();
  ImGui::Checkbox("SHOW DATE", &showDate_);

  //my_imgui.addSpace(1);
  my_imgui.setPositionX(130.0f);
  ImGui::Checkbox("MUTE SOUND", &mute);

  //my_imgui.addSpace(1);
  ImGui::TextUnformatted(getActualTime());

  setX(pos_x);
  setY(pos_y);
}

//GETTERS
int Clock::getHour() {
  return hour;
}

int Clock::getMinute() {
  return minute;
}

int Clock::getSecond() {
  return second;
}

char* Clock::getHourString() {
  /*Convert hours to char*/
  static char hours_number[3] = "\0";
  memset(hours_number, '\0', sizeof(hours_number));
  if(getHour() < 10) {
    sprintf(hours_number, "0%d", getHour());
  }else{
    sprintf(hours_number, "%d", getHour());
  }
  return hours_number;
}

char* Clock::getMinuteString() {
  /*Convert minutes to char*/
  static char minutes_number[3] = "\0";
  memset(minutes_number, '\0', sizeof(minutes_number));
  if(getMinute() < 10) {
    sprintf(minutes_number, "0%d", getMinute());
  }else{
    sprintf(minutes_number, "%d", getMinute());
  }
  return minutes_number;
}

char* Clock::getSecondString() {
  /*Convert seconds to char*/
  static char seconds_number[3] = "\0";
  memset(seconds_number, '\0', sizeof(seconds_number));
  if(getSecond() < 10) {
    sprintf(seconds_number, "0%d", getSecond());
  }else{
    sprintf(seconds_number, "%d", getSecond());
  }
  return seconds_number;
}

int Clock::getDayNumber() {
  return (tm.tm_mday);
}

int Clock::getMonthNumber() {
  return (1 + tm.tm_mon);
}

int Clock::getYearNumber() {
  return (1900 + tm.tm_year);
}

char* Clock::getYear() {
  /*Convert year to char*/
  int aux_year = 1900 + tm.tm_year;
  sprintf(year_, "%d", aux_year);
  return year_;
}

char* Clock::getMonth() {
  /*Convert month to char*/
  static char month_number[3] = "\0";
  memset(month_number, '\0', sizeof(month_number));
  if(tm.tm_mon < 10) {
    sprintf(month_number, "0%d", tm.tm_mon + 1);
  }else{
    sprintf(month_number, "%d", tm.tm_mon + 1);
  }
  return month_number;
}

char* Clock::getDay() {
  /*Convert day to char*/
  static char day_number[3] = "\0";
  memset(day_number, '\0', sizeof(day_number));
  if(tm.tm_mday < 10) {
    sprintf(day_number, "0%d", tm.tm_mday);
  }else{
    sprintf(day_number, "%d", tm.tm_mday);
  }
  return day_number;
}

char* Clock::getMonthName() {
  return *(months + tm.tm_mon);
}

char* Clock::getDayName() {
  return *(days + tm.tm_wday);
}

char* Clock::getActualTime() {
  return actualTime_;
}

char* Clock::getTotalDate() {
  static char tmp[33] = "\0";
  memset(tmp, '\0', sizeof(tmp));
  strcat(tmp, getDay());
  strcat(tmp, "/");
  strcat(tmp, getMonth());
  strcat(tmp, "/");
  strcat(tmp, getYear());
  return tmp;
}

//BIRTHDAYS GETTERS FORM DATABASE

        //AUXILIARY FUNCTIONS
int isLeapYear(int year, int mon) {
  int flag = 0;
  if (year % 100 == 0) {
    if (year % 400 == 0) {
      if (mon == 2) {
        flag = 1;
      }
    }
  }else if (year % 4 == 0) {
    if (mon == 2) {
      flag = 1;
    }
  }
  return (flag);
}

int countLeapYears(int year, int mon) {
  int aux_year = year;

  // Check if the current year needs to be
  //  considered for the count of leap years
  // or not
  if (mon <= 2)
      aux_year--;

  // An year is a leap year if it
  // is a multiple of 4,
  // multiple of 400 and not a
    // multiple of 100.
  return (aux_year / 4)
          - (aux_year / 100)
          + (aux_year / 400);
}

int getDifference(int y1, int m1, int d1, int y2, int m2, int d2) {
    // COUNT TOTAL NUMBER OF DAYS
    // BEFORE FIRST DATE 'dt1'
 
    // initialize count using years and day
    long int n1 = y1 * 365 + d1;
 
    // Add days for months in given date
    for (int i = 0; i < m1 - 1; i++)
        n1 += DaysInMon[i];
 
    // Since every leap year is of 366 days,
    // Add a day for every leap year
    n1 += countLeapYears(y1, m1);
 
    // SIMILARLY, COUNT TOTAL NUMBER OF
    // DAYS BEFORE 'dt2'
 
    long int n2 = y2 * 365 + d2;
    for (int i = 0; i < m2 - 1; i++)
        n2 += DaysInMon[i];
    n2 += countLeapYears(y2, m2);
 
    // return difference between two counts
    return (n2 - n1);
}

long int calcDayNumFromDate(int y, int m, int d) {
  m = (m + 9) % 12;
  y -= m / 10;
  long int dn = 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + (d - 1);

  return dn;
}

std::string CalcDayOfWeek(int y, int m, int d) {

  std::string day[] = {
    "WEDNESDAY",
    "THURSDAY",
    "FRIDAY",
    "SATURDAY",
    "SUNDAY",
    "MONDAY",
    "TUESDAY"
  };

  long int dn = calcDayNumFromDate(y, m, d);

  return day[dn % 7];
}

        //RETRUN FUNCTIONS
int Clock::getTotalAge(databaseinfo *current_user, int user, const char* date) {
  int bornYear = atoi(current_user->table_data[0][4 + (6 * user)].c_str()); //AÑO
  int bornMonth = 0; //MES
  for(int i = 1; i < 13; i++) {
    if(strcmp(current_user->table_data[0][3 + (6 * user)].c_str(), monthsItems[i]) == 0){
      bornMonth = i;
    }
  }
  int bornDay =  atoi(current_user->table_data[0][2 + (6 * user)].c_str()); //DÍA

  int year_aux = bornYear; 
  int month_aux = bornMonth;
  int days_aux = bornDay;
  days_aux = DaysInMon[month_aux - 1] - days_aux; //+1
  /*CHECK FOR LEAP YEAR*/
  if (isLeapYear(year_aux, month_aux)) {
    days_aux = days_aux + 1;
  }
  /*CALCULATE AGE*/
  days_aux = days_aux + getDayNumber();
  month_aux = (12 - month_aux) + (getMonthNumber() - 1);
  year_aux = getYearNumber() - year_aux - 1;
  /*CHECKING FOR LEAP YEAR FEB 29*/
  if (isLeapYear(getYearNumber(), getMonthNumber())) {
    if (days_aux >= (DaysInMon[getMonthNumber() - 1] + 1)) {
      days_aux = days_aux - (DaysInMon[getMonthNumber() - 1] + 1);
      month_aux = month_aux + 1;
    }
  }
  else if (days_aux >= DaysInMon[getMonthNumber() - 1]) {
    days_aux = days_aux - (DaysInMon[getMonthNumber() - 1]);
    month_aux = month_aux + 1;
  }
  if (month_aux >= 12) {
    year_aux = year_aux + 1;
    month_aux = month_aux - 12;
  }
  switch(MAKECODE(date)){
    case MAKECODE("day"): return days_aux;
    break;
    case MAKECODE("month"): return month_aux;
    break;
    case MAKECODE("year"): return year_aux;
    break;
  }
  return 0;
}

std::string Clock::getWeekDay(databaseinfo *current_user, int user) {
  int bornYear = atoi(current_user->table_data[0][4 + (6 * user)].c_str()); //AÑO
  int bornMonth = 0; //MES
  for(int i = 1; i < 13; i++) {
    if(strcmp(current_user->table_data[0][3 + (6 * user)].c_str(), monthsItems[i]) == 0){
      bornMonth = i;
    }
  }
  int bornDay =  atoi(current_user->table_data[0][2 + (6 * user)].c_str()); //DÍA

  std::string dow = CalcDayOfWeek(bornYear, bornMonth, bornDay);
  
  return dow;
}

float Clock::getTotalMonthsLived(databaseinfo *current_user, int user) {
  float totalYears  = (float)getTotalAge(current_user, user, "year");
  float totalMonths = (float)getTotalAge(current_user, user, "month");
  float totalDays   = (float)getTotalAge(current_user, user, "day");
  totalYears = totalYears * 12.0f;
  totalDays = totalDays/30.0f;

  totalMonths += totalDays + totalYears;

  return totalMonths;
}

int Clock::getTotalDaysLived(databaseinfo *current_user, int user) {
  int bornYear = atoi(current_user->table_data[0][4 + (6 * user)].c_str()); //AÑO
  int bornMonth = 0; //MES
  for(int i = 1; i < 13; i++) {
    if(strcmp(current_user->table_data[0][3 + (6 * user)].c_str(), monthsItems[i]) == 0){
      bornMonth = i;
    }
  }
  int bornDay =  atoi(current_user->table_data[0][2 + (6 * user)].c_str()); //DÍA

  int result = getDifference(bornYear, bornMonth, bornDay, getYearNumber(), getMonthNumber(), getDayNumber());

  return result;
}

int Clock::getTotalHoursLived(int days_lived) {
  int aux_hours = 0;
  aux_hours = days_lived * 24;
  aux_hours += getHour();

  return aux_hours;
}

int Clock::getTotalMinutesLived(int hours_lived) {
  int aux_minutes = 0;
  aux_minutes = hours_lived * 60;
  aux_minutes += getMinute();

  return aux_minutes;
}

unsigned long Clock::getTotalSecondsLived(int minutes_lived) {
  unsigned long aux_seconds = 0;
  aux_seconds = minutes_lived * 60;
  aux_seconds += getSecond();

  return aux_seconds;
}

int Clock::getNextBirthday(databaseinfo *current_user, int user, const char* date) {
  int bornMonth = 0; //MES
  for(int i = 1; i < 13; i++) {
    if(strcmp(current_user->table_data[0][3 + (6 * user)].c_str(), monthsItems[i]) == 0){
      bornMonth = i;
    }
  }
  int bornDay =  atoi(current_user->table_data[0][2 + (6 * user)].c_str()); //DÍA

  int year_aux = getYearNumber();
  int month_aux = getMonthNumber();
  int days_aux = getDayNumber();

  if(days_aux >= bornDay) {
    days_aux -= bornDay;
  }else {
    month_aux--;
    days_aux += 30;
    days_aux -= bornDay;
  }if (month_aux >= bornMonth) {
    month_aux -= bornMonth;
  }else {
    //bornYear--;
    month_aux += 12;
    month_aux = month_aux - bornMonth;
  }
  if(getMonthNumber() >= bornMonth) {
    if(getDayNumber() > bornDay) {
      year_aux++;
    }

    if(getDayNumber() < bornDay) {
      year_aux = getYearNumber();
    }
    
    if(getDayNumber() == bornDay) {
      year_aux++;
    }
  }

  month_aux = 11 - month_aux;
  days_aux= 29 - days_aux;

  int hours_aux = 23 - getHour();
  int minutes_aux = 59 - getMinute();
  int seconds_aux = 60 - getSecond();

  switch(MAKECODE(date)){
    case MAKECODE("second"): return seconds_aux;
    break;
    case MAKECODE("minute"): return minutes_aux;
    break;
    case MAKECODE("hour"): return hours_aux;
    break;
    case MAKECODE("day"): return days_aux;
    break;
    case MAKECODE("month"): return month_aux;
    break;
    case MAKECODE("year"): return year_aux;
    break;
  }
  return 0;
}

int Clock::getTotalDaysUntilBirthday(databaseinfo *current_user, int user) {
  int bornMonth = 0; //MES
  for(int i = 1; i < 13; i++) {
    if(strcmp(current_user->table_data[0][3 + (6 * user)].c_str(), monthsItems[i]) == 0){
      bornMonth = i;
    }
  }
  int bornDay =  atoi(current_user->table_data[0][2 + (6 * user)].c_str()); //DÍA

  int result = 0;
  if(getMonthNumber() > bornMonth){
    result = getDifference(getYearNumber(), getMonthNumber(), getDayNumber(), getYearNumber() + 1, bornMonth, bornDay) - 1;
  }
  if(getMonthNumber() == bornMonth) {
    result = getDifference(getYearNumber(), getMonthNumber(), getDayNumber(), getYearNumber(), bornMonth, bornDay);
    if(getDayNumber() > bornDay) {
      result = 365 - abs(result);
    }

    if(getDayNumber() < bornDay) {
      result = result;
    }
    
    if(getDayNumber() == bornDay) {
      result = 0;
    }
    
  }
  if (getMonthNumber() < bornMonth){
    result = getDifference(getYearNumber(), getMonthNumber(), getDayNumber(), getYearNumber(), bornMonth, bornDay) - 1;
  }

  return abs(result);
}

int Clock::getTotalHoursUntilBirthday(int days_left) {
  int aux_hours = 0;
  aux_hours = days_left * 24;
  if(days_left > 0){
    aux_hours -= (getHour() + 1);
  }

  return aux_hours;
}

int Clock::getTotalMinutesUntilBirthday(int hours_left) {
  int aux_minutes = 0;
  aux_minutes = hours_left * 60;
  if(hours_left > 0){
    aux_minutes -= getMinute();
  }
  if(hours_left == 0) {
    aux_minutes = 59 - getMinute();
  }
  
  return aux_minutes;
}

int Clock::getTotalSecondsUntilBirthday(int minutes_left) {
  int aux_seconds = 0;
  aux_seconds = minutes_left * 60;
  if(minutes_left > 0) {
    aux_seconds -= getSecond();
  }
  if(minutes_left == 0) {
    aux_seconds = 60 - getSecond();
  }

  return aux_seconds;
}

std::string Clock::getZodiacName(databaseinfo *current_user, int user) {
  std::string zodiacName = "\0";
  int bornMonth = 0; //MES
  for(int i = 1; i < 13; i++) {
    if(strcmp(current_user->table_data[0][3 + (6 * user)].c_str(), monthsItems[i]) == 0){
      bornMonth = i;
    }
  }
  int bornDay =  atoi(current_user->table_data[0][2 + (6 * user)].c_str()); //DÍA

  switch(bornMonth) {
    //January
    case 1: 
      if(bornDay <= 20) {
        zodiacName = "CAPRICORN";
      }else{
        zodiacName = "AQUARIUS";
      }
    break;
    //February
    case 2:
      if(bornDay <= 18) {
        zodiacName = "AQUARIUS";
      }else{
        zodiacName = "PISCES";
      }
    break;
    //March
    case 3:
      if(bornDay <= 20) {
        zodiacName = "PISCES";
      }else{
        zodiacName = "ARIES";
      }
    break;
    //April
    case 4:
      if(bornDay <= 19) {
        zodiacName = "ARIES";
      }else{
        zodiacName = "TAURUS";
      }
    break;
    //May
    case 5:
      if(bornDay <= 20) {
        zodiacName = "TAURUS";
      }else{
        zodiacName = "GEMINI";
      }
    break;
    //June
    case 6:
      if(bornDay <= 20) {
        zodiacName = "GEMINI";
      }else{
        zodiacName = "CANCER";
      }
    break;
    //July
    case 7:
      if(bornDay <= 22) {
        zodiacName = "CANCER";
      }else{
        zodiacName = "LEO";
      }
    break;
    //August
    case 8:
      if(bornDay <= 22) {
        zodiacName = "LEO";
      }else{
        zodiacName = "VIRGO";
      }
    break;
    //September
    case 9:
      if(bornDay <= 22) {
        zodiacName = "VIRGO";
      }else{
        zodiacName = "LIBRA";
      }
    break;
    //October
    case 10:
      if(bornDay <= 22) {
        zodiacName = "LIBRA";
      }else{
        zodiacName = "SCORPIO";
      }
    break;
    //November
    case 11:
      if(bornDay <= 21) {
        zodiacName = "SCORPIO";
      }else{
        zodiacName = "SAGITTARIUS";
      }
    break;
    //December
    case 12:
      if(bornDay <= 21) {
        zodiacName = "SAGITTARIUS";
      }else{
        zodiacName = "CAPRICORN";
      }
    break;
  }

  return zodiacName;
}

std::string Clock::getNextWeekDayOfBirthday(databaseinfo *current_user, int user) {
  int aux_year  = getNextBirthday(current_user, user, "year");
  int aux_month = 0;
    for(int i = 1; i < 13; i++) {
    if(strcmp(current_user->table_data[0][3 + (6 * user)].c_str(), monthsItems[i]) == 0){
      aux_month = i;
    }
  }
  int aux_day = atoi(current_user->table_data[0][2 + (6 * user)].c_str()); //DÍA

  std::string dow = CalcDayOfWeek(aux_year, aux_month, aux_day);
  
  return dow;
}

//FREE POINTERS
void Clock::freeDatePointers() {
  free(days); days=nullptr;
	free(months); months=nullptr;
}

void Clock::freePointers() {
  TTF_CloseFont(font16);
  TTF_CloseFont(font20);
  TTF_CloseFont(font20_outline);
  
  freeDatePointers();

  Mix_FreeChunk(clock1_);
  Mix_FreeChunk(clock2_);

  for(int i = 1; i < 13; i++) {
    my_texture.releaseTextures(hours_[i]);
  }
  releaseVector(hour_vector_);

  sound.destroySound();
}

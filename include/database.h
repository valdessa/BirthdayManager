/**
 * @file   database.h
 * @brief  database base header file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
*/

#ifndef __DATABASE_H__
#define __DATABASE_H__ 1

#include "entity.h"
#include "my_imgui.h"
#include "clock.h"
#include "sqlite3.h"
#include "kirby.h"
#include <string.h>
#include <vector>
#include <string>

struct databaseinfo {
  std::vector<std::string> table_names;
  std::vector<std::string> *column_names;
  std::vector<std::string> *table_data;
  std::vector<std::string> *insert_values;
  //std::vector<Vector4> *ColorData; //Used only with ImGui Color Changer!!
  std::vector<std::string> *aux_data;
  std::vector<int> *selectedMonth;
  std::vector<int> *selectedDay;
  bool is_table;
  int aux = 0;
};

struct createdb{
  std::string table_name;
  char aux[25];
  std::vector<std::string> column_names;
};

struct DBData {
  char data[100];
  //Vector columnName;
  //Vector columnContent;
  //u16 NTables;           //Number of tables of the DB
  //u16 NColumns;          //Number of columns of the Table
  //u16 NRows;             //Number of rows of the Table
};

class Database : public Entity {
 public:

  //INIT
  void initDB();

  //LOAD AND SAVE DATABASE
  int LoadDataBase(databaseinfo *current_db, const char *path);
  int SaveDataBase(databaseinfo *current_db, const char *path);
  void UpdateAuxData(databaseinfo *current_db);

  //INSERT INTO THE DATABASE
  int CreateTable(const char *path);
  int InsertDataBase(databaseinfo *current_db, const char *path, int table);

  //INSERT INTO THE BIRTHDAY DATABASE
  int InsertBirthdayDataBase(int table);
  void AssignAMonth();
  void AssignADay();

  //EXTRA THINGS
  bool IsRepeated();
  void cleanVariables();

  //DATABASE MANAGEMENT POP UPS
  void CreateTablePopUp();
  void DestroyTablePopUp();
  void AddColumnPopUp(int table);
  void DeleteColumnPopUp(int table);
  void DeleteRowPopUp(databaseinfo *current_db, const char *path, int table);

  //SHOW DATABASE
  void bottomButtonsDB();
  void DataBaseImGui();
  void ImGuiColorChanger();

  //SHOW BIRTHDAY DATABASE
  void bottomButtonsBirthdayDB();
  void BirthdayDataBaseImGui();
  void BirthdayUsers();
  void NextBirthdaysInThisMonths();
  void BirthdaysToday(Kirby *act_kirby);

  //FREE DATABASE
  void FreeDB();

  databaseinfo data_base;   //Usado para las tablas normales
  databaseinfo birthday_db; //Usado para las tablas de cumpleanyos
  databaseinfo color_db;    //Usado para las tablas de color de estilos de ImGui
  createdb creator;
  MyImGui DB_imgui; 
  Clock DB_clock;

  char* db_path = "../data/database.db";
  char* birthday_db_path = "../data/birthday.db";
  char* styles_db_path = "../data/styles.db";

 protected:
	//sqlite3* db = nullptr;
  int handler;
};

//CALLBACKS
int DataBaseLoad(void *notused, int argc, char **argv, char **azcolname);
int DataBaseLoadTables(void *notused, int argc, char **argv, char **azcolname);


#endif

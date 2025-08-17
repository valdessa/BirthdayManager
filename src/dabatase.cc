#include "database.h"

//DATABASE CALLBACKS
int DataBaseLoad(void *notused, int argc, char **argv, char **azcolname) {
  databaseinfo *p = (databaseinfo *)notused;
  azcolname; argc;
  std::string aux(argv[0]);

  if(strcmp(aux.c_str(),"sqlite_sequence")){
    p->table_names.push_back(aux);
  }

  return 0;
}

int DataBaseLoadTables(void *notused, int argc, char **argv, char **azcolname) {
  databaseinfo *p = (databaseinfo *)notused;

  for(int i = 0 ; i < argc ; ++i){
    if(!p->is_table){
      std::string aux1(azcolname[i]);
      p->column_names[p->aux].push_back(aux1);
    }
    if(NULL != argv[i]){
      std::string aux2(argv[i]);
      p->table_data[p->aux].push_back(aux2);
      p->aux_data[p->aux].push_back(aux2);
    }else{
      p->table_data[p->aux].push_back("NULL");
      p->aux_data[p->aux].push_back("NULL");
    }
  }
    p->is_table = true;

    return 0;
  }

//INIT
void Database::initDB() {
  LoadDataBase(&data_base, db_path);
  LoadDataBase(&birthday_db, birthday_db_path);
  LoadDataBase(&color_db, styles_db_path);

  AssignAMonth();
  AssignADay();
}

void Database::AssignAMonth(){
  for(int i = 0 ; i < (int)birthday_db.table_names.size() ;++i){
    int row = 0;
    if ((int)birthday_db.column_names[i].size() != 0) {
      row = ((int)birthday_db.table_data[i].size() / (int)birthday_db.column_names[i].size());
    }
    for(int n = 0; n < row; n++){
      birthday_db.selectedMonth[i].push_back(0);
      //printf("%d\n", (int)birthday_db.selectedMonth[i][n]);
    }
  }

  int aux = 1;
  for(int i = 0 ; i < (int)birthday_db.table_names.size() ;++i){
    for (int cell = 0; cell <  (int)birthday_db.table_data[i].size(); cell++){
      int result = cell%(int)birthday_db.column_names[i].size();
      switch(result) {
        case 3:
          if(aux < (int)birthday_db.selectedMonth[i].size() + 1){
            int aux_result;
            if(aux == 1){
              aux_result = (cell - result);
            }else{
              aux_result = (cell - (result * aux));
              aux_result = (aux_result/result);
            }
            for(int j = 1; j < 13; j++) {
              if(strcmp(birthday_db.table_data[i][cell].c_str(), monthsItems[j]) == 0){
                //printf("COINCIDENCE!!\n");
                //printf("IN THE USER: %s WITH BORN MONTH: %s \n", birthday_db.table_data[i][cell - 3].c_str(), birthday_db.table_data[i][cell].c_str());
                birthday_db.selectedMonth[i][aux_result] = j;
              }
            }
            aux ++;
          }
        break;
        default:
        break;
      }
    }
  }
}

void Database::AssignADay(){
  for(int i = 0 ; i < (int)birthday_db.table_names.size() ;++i){
    int row = 0;
    if ((int)birthday_db.column_names[i].size() != 0) {
      row = ((int)birthday_db.table_data[i].size() / (int)birthday_db.column_names[i].size());
    }
    for(int n = 0; n < row; n++){
      birthday_db.selectedDay[i].push_back(0);
      //printf("%d\n", (int)birthday_db.selectedDay[i][n]);
    }
  }

  int aux = 1;
  for(int i = 0 ; i < (int)birthday_db.table_names.size() ;++i){
    for (int cell = 0; cell <  (int)birthday_db.table_data[i].size(); cell++){
      int result = cell%(int)birthday_db.column_names[i].size();
      switch(result) {
        case 2:
          if(aux < (int)birthday_db.selectedDay[i].size() + 1){
            int aux_result;
            if(aux == 1){
              aux_result = (cell - result);
            }else{
              aux_result = (cell - result);
              aux_result = (aux_result/6);
            }
            for(int j = 1; j < 32; j++) {
              if(strcmp(birthday_db.table_data[i][cell].c_str(), daysItems[j]) == 0){
                //printf("COINCIDENCE!!\n");
                //printf("IN THE USER: %s WITH BORN DAY: %s \n", birthday_db.table_data[i][cell - 2].c_str(), birthday_db.table_data[i][cell].c_str());
                birthday_db.selectedDay[i][aux_result] = j;
              }
            }
            aux ++;
          }
        break;
        default:
        break;
      }
    }
  }
}

//EXTRA THINGS
bool Database::IsRepeated(){
  for(int i = 0 ; i < (int)creator.column_names.size() ;++i){
    if(!strcmp(creator.aux,creator.column_names[i].c_str())){
      return true;
    }
  }
  return false;
}

void Database::cleanVariables() {
  memset(creator.aux,'\0',sizeof(creator.aux));


  for(int i = 0 ; i < (int)data_base.table_names.size() ;++i){
    for(int k = 0 ; k < (int)data_base.column_names[i].size() ; ++k){
      data_base.insert_values[i][k].clear(); //limpiar el espacio roñoso ese
    }
  }

    for(int i = 0 ; i < (int)birthday_db.table_names.size() ;++i){
    for(int k = 0 ; k < (int)birthday_db.column_names[i].size() ; ++k){
      birthday_db.insert_values[i][k].clear(); //limpiar el espacio roñoso ese
    }
  }

  //AssignAMonth();

  /*for(int i = 0 ; i < (int)birthday_db.table_names.size() ;++i){
    int row = (int)birthday_db.table_data[i].size() / (int)birthday_db.column_names[i].size();
    for(int n = 0; n < row; n++){
      birthday_db.selectedMonth[i].push_back(0);
      printf("%d\n", (int)birthday_db.selectedMonth[i][n]);
    }
  }*/

}

//LOAD AND SAVE DATA
int Database::LoadDataBase(databaseinfo *current_db, const char *path){
  sqlite3* db = nullptr;
  char *sql = "SELECT name FROM sqlite_master where type ='table'";

  handler = sqlite3_open(path, &db);
  handler = sqlite3_exec(db, sql, DataBaseLoad, (void *)current_db, 0);

  if (handler != SQLITE_OK) {
    printf("\n\tError executing SQL sentence!!");
    sqlite3_close(db);
    return 1;
  }

   current_db->column_names  = new std::vector<std::string>[current_db->table_names.size()];
   current_db->table_data    = new std::vector<std::string>[current_db->table_names.size()];
   current_db->insert_values = new std::vector<std::string>[current_db->table_names.size()];
   current_db->aux_data      = new std::vector<std::string>[current_db->table_names.size()];
   current_db->selectedMonth = new std::vector<int>[current_db->table_names.size()];
   current_db->selectedDay   = new std::vector<int>[current_db->table_names.size()];

  for(int i = 0 ; i < (int)current_db->table_names.size() ; i++){
    char sql_sentence[255] = "SELECT * FROM ";
    current_db->is_table = false;
    strcat(sql_sentence,current_db->table_names[i].c_str());
    handler = sqlite3_open(path, &db);
    handler = sqlite3_exec(db, sql_sentence, DataBaseLoadTables, (void *)current_db, 0);
    current_db->aux ++;
  }
    current_db->aux = 0;

  if (handler != SQLITE_OK) {
    printf("\n\tError executing SQL sentence!! 4");
    sqlite3_close(db);
    return 1;
  }
  for(int i= 0; i < (int)current_db->table_names.size() ;i++){
    for(int j= 0 ; j < (int)current_db->column_names[i].size(); j++){
      current_db->insert_values[i].push_back(" ");
    }
  }
  cleanVariables();

  sqlite3_close(db);
  return 0;
}

int Database::SaveDataBase(databaseinfo *current_db, const char *path){
  sqlite3* db = nullptr;
  char sql[1024];
  memset(sql,'\0',sizeof(sql));

  for(int i = 0 ; i < (int)current_db->table_names.size() ;++i){
    for (int cell = 0; cell <  (int)current_db->table_data[i].size(); cell++){
      if(strcmp(current_db->table_data[i][cell].c_str(),current_db->aux_data[i][cell].c_str())){
        strcat(sql,"UPDATE ");
        strcat(sql,current_db->table_names[i].c_str());
        strcat(sql," SET ");
        strcat(sql,current_db->column_names[i][cell%current_db->column_names[i].size()].c_str());
        strcat(sql,"='");
        strcat(sql,current_db->table_data[i][cell].c_str());
        strcat(sql,"' WHERE ");
        strcat(sql,current_db->column_names[i][0].c_str());
        strcat(sql,"='");
        strcat(sql,current_db->aux_data[i][cell - (cell%current_db->column_names[i].size())].c_str());
        strcat(sql,"';");
      }
    }
  }
    strcat(sql,"\0");
    printf("%s\n",sql);

  if(sql != NULL){
    handler = sqlite3_open(path, &db);
    handler = sqlite3_exec(db, sql, NULL, (void *)current_db, 0);
  }

  if (handler != SQLITE_OK) {
    printf("\n\tError executing SQL sentence!! 10");
    sqlite3_close(db);
    return 1;
  }

  sqlite3_close(db);
  return 0;
}

void Database::UpdateAuxData(databaseinfo *current_db){
  for(int i = 0 ; i < (int)current_db->table_names.size() ;++i){
    current_db->aux_data[i].clear();
  }
  for(int i = 0 ; i < (int)current_db->table_names.size() ;++i){
    for (int cell = 0; cell <  (int)current_db->table_data[i].size(); cell++){
      current_db->aux_data[i].push_back(current_db->table_data[i][cell].c_str());
    }
  }
}

//INSERT INTO THE DATABASE
int Database::InsertDataBase(databaseinfo *current_db, const char *path, int table){
  sqlite3* db = nullptr;
  char tmp[5];
  int tmp2 = current_db->table_data[table].size()/current_db->column_names[table].size() + 1;
  sprintf(tmp,"%d",tmp2);
  //_____________________TABLE 1
  char sql[1024];
  memset(sql,'\0',sizeof(sql));

  strcat(sql,"INSERT INTO ");
  strcat(sql,current_db->table_names[table].c_str());
  strcat(sql," (");
  for(int i = 0 ; i < (int)current_db->column_names[table].size();i++){
    strcat(sql,current_db->column_names[table][i].c_str());
    if(i < (int)current_db->column_names[table].size()-1)
      strcat(sql,",");
  }
  strcat(sql,") VALUES ('");
  strcat(sql,tmp);
  strcat(sql,"'");
  strcat(sql,",");
  for(int i = 1 ; i < (int)current_db->insert_values[table].size();i++){
    strcat(sql,"'");
    strcat(sql,current_db->insert_values[table][i].c_str());
    strcat(sql,"'");
    if(i < (int)current_db->insert_values[table].size()-1)
      strcat(sql,",");
  }
  strcat(sql,");");

  for(int i = 0; i < (int)current_db->insert_values[table].size() ; i++){
    if( i == 0 ){
      current_db->table_data[table].push_back(tmp);
    }else{
      current_db->table_data[table].push_back(current_db->insert_values[table][i].c_str());
    }
  }
  UpdateAuxData(current_db);

  if(sql != NULL){
    handler = sqlite3_open(path, &db);
    handler = sqlite3_exec(db, sql, NULL, (void *)&current_db, 0);
    printf("%s\n", sql);
  }

  if (handler != SQLITE_OK) {
    printf("\n\tError executing SQL sentence!! 10\n");
    sqlite3_close(db);
    return 1;
  }

  sqlite3_close(db);
  return 0;
}

int Database::CreateTable(const char *path){
  sqlite3* db = nullptr;
  char sql[1024];
  memset(sql,'\0',sizeof(sql));

  strcat(sql,"CREATE TABLE ");
  strcat(sql,creator.table_name.c_str());
  strcat(sql," (ID INTEGER PRIMARY KEY AUTOINCREMENT,");
  for(int i = 0 ; i < (int)creator.column_names.size();i++){
    strcat(sql,creator.column_names[i].c_str());
    strcat(sql," VARCHAR");
    if(i < (int)creator.column_names.size()-1)
      strcat(sql,",");
  }
  strcat(sql,");");
  strcat(sql,"INSERT INTO ");
  strcat(sql,creator.table_name.c_str());
  strcat(sql," (");
  for(int i = 0 ; i < (int)creator.column_names.size();i++){
    strcat(sql,creator.column_names[i].c_str());
    if(i < (int)creator.column_names.size()-1)
      strcat(sql,",");
  }
  strcat(sql,") VALUES (");
  //para la tabla cumple:
  if(strcmp(path, birthday_db_path) == 0){
    DB_clock.updateTimerClock();
    char new_year[5] = "\0";
    for(int i = 0 ; i < (int)creator.column_names.size();i++){
      switch(i) {
        case 0: strcat(sql,"'COVID-19'");
        break;
        case 1: strcat(sql,"'08'");
        break;
        case 2: strcat(sql,"'December'");
        break;
        case 3:
          sprintf(new_year, "%d", 2019);
          strcat(sql,"'");
          strcat(sql, new_year);
          strcat(sql,"'");
        break;
        case 4:
          strcat(sql,"'");
          strcat(sql, DB_clock.getTotalDate());
          strcat(sql, " ");
          strcat(sql, DB_clock.getHourString());
          strcat(sql, ":");
          strcat(sql, DB_clock.getMinuteString());
          strcat(sql, ":");
          strcat(sql, DB_clock.getSecondString());
          strcat(sql,"'");
        break;
      }
      if(i < (int)creator.column_names.size()-1)
        strcat(sql,",");
    }
  //para la tabla de tablas normales:
  }else{
    for(int i = 0 ; i < (int)creator.column_names.size();i++){
      strcat(sql,"''");
      if(i < (int)creator.column_names.size()-1)
        strcat(sql,",");
    }
  }
  strcat(sql,");");

  strcat(sql,"\0");
  printf("%s\n",sql);

  if(sql != NULL){
    handler = sqlite3_open(path, &db);
    handler = sqlite3_exec(db, sql, NULL, NULL, 0);
  }

  if (handler != SQLITE_OK) {
    printf("\n\tError executing SQL sentence!! 10");
    sqlite3_close(db);
    return 1;
  }

  sqlite3_close(db);
  return 0;
}

//DATABASE MANAGEMENT POP UPS
void Database::CreateTablePopUp() {

  ImGui::InputText("Table name",(char*)creator.table_name.c_str(),25);
  ImGui::InputText("Column name",creator.aux,25);
  static bool pulsatedTable = false;
  static bool pulsatedColumn = false;
  static bool repeatedColumn = false;
  static bool created = false;
  static char aux_name[33] = "\0";
  DB_imgui.SetButtonColor("green");
  if(ImGui::Button("Add Column") && !repeatedColumn){
    pulsatedColumn = true;
    if(strlen(creator.aux) > 0 && !IsRepeated()) {
      pulsatedColumn = false;
      creator.column_names.push_back(creator.aux);
    }
    memset(creator.aux,'\0',sizeof(creator.aux));

  }
  ImGui::SameLine();

  if(ImGui::Button("Create Table")){
    pulsatedTable = true;
    if(creator.column_names.size() > 0){
      pulsatedColumn = false;
    }else{
      pulsatedColumn = true;
    }
    if(creator.column_names.size() > 0 && strlen(creator.table_name.c_str()) > 0){
      created = true;
      pulsatedTable = false;
      CreateTable(db_path);
      memset(aux_name,'\0',sizeof(aux_name));
      strcpy(aux_name, creator.table_name.c_str());
      creator.table_name.clear();
      creator.column_names.clear();
      memset(creator.aux,'\0',sizeof(creator.aux));
      FreeDB();
      initDB();
    }
  }
  DB_imgui.SetButtonColor("blue");

  ImGui::SameLine();
  if(ImGui::Button("Close")){
    pulsatedTable = false;
    pulsatedColumn = false;
    repeatedColumn = false;
    created = false;
    creator.table_name.clear();
    creator.column_names.clear();
    ImGui::CloseCurrentPopup();
  }
  //printf("[%s]\n", (char*)creator.table_name.c_str());
  if(strcmp((char*)creator.table_name.c_str(), "") == 0 && pulsatedTable) {
    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "Set a name to the Table first!!");
  }

  if (creator.table_name.size() == 0 && pulsatedColumn && !repeatedColumn){
    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "Set a name to the Column first!!");
  }

  if(strlen(creator.aux) > 0 && IsRepeated()) {
    repeatedColumn = true;
    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "This Column exists, insert a different Column Name");
  }else{
    repeatedColumn = false;
  }

  if(created && strlen(creator.table_name.c_str()) == 0) {
    ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Table"); ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), aux_name); ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Created Succesfully :D");
  }else if (strlen(creator.table_name.c_str()) > 0) {
    created = false;
  }

  for(int i = 0 ; i < (int)creator.column_names.size() ;++i){
    char buffer[33] = "Column[";
    char aux_buffer[10] = "\0";
    sprintf(aux_buffer, "%02d", i);
    strcat(buffer, aux_buffer);
    strcat(buffer, "] Added: ");
    ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), buffer);
    ImGui::SameLine();
    ImGui::Text(creator.column_names[i].c_str());
    memset(buffer, '\0', sizeof(buffer));
  }
  ImGui::EndPopup();
}

void Database::DestroyTablePopUp() {
  sqlite3* db = nullptr;
  ImGui::TextColored(ImVec4(0.0f,0.0f,1.0f,1.0f), "Insert the Table's name that you want to delete");
  ImGui::InputText("Name of the Table", creator.aux, 25);
  static bool exist = false;
  static bool pulsated = false;

  DB_imgui.SetButtonColor("red");
  if(ImGui::Button("Destroy Table")) {
    pulsated = true;
    for(int i = 0 ; i < (int)data_base.table_names.size() ;++i) {
      if(strcmp(data_base.table_names[i].c_str(), creator.aux) == 0) {
          exist = true;
          pulsated = false;
          char sql_drop_table[255] = {"\0"};
          strcat(sql_drop_table, "DROP TABLE ");
		      strcat(sql_drop_table, data_base.table_names[i].c_str());
          printf("SQL DESTROY: %s\n", sql_drop_table);
          handler = sqlite3_open(db_path, &db);
          handler = sqlite3_exec(db, sql_drop_table, 0, 0, 0);
          memset(creator.aux,'\0',sizeof(creator.aux));
          FreeDB();
          initDB();
       }
    }
  }
  DB_imgui.SetButtonColor("blue");

  ImGui::SameLine();
  if(ImGui::Button("Close")) {
    exist = false;
    pulsated = false;
    memset(creator.aux,'\0',sizeof(creator.aux));
    ImGui::CloseCurrentPopup();
  }

  if(exist && strlen(creator.aux) == 0) {
    ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Table deleted Succesfully :D");
  }else if (strlen(creator.aux) > 0) {
    exist = false;
  }

  if(pulsated && !exist) {
    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "The Table doesn't exists :/");
  }
  ImGui::EndPopup();
}

void Database::AddColumnPopUp(int table) {
  sqlite3* db = nullptr;
  ImGui::TextColored(ImVec4(0.0f,0.0f,1.0f,1.0f), "Insert the Name of the new Column that you want to add");
  ImGui::InputText("Name of the new Column", creator.aux, 25);

  static bool exist = false;
  static bool pulsated = false;
  static bool doitonce = false;
  DB_imgui.SetButtonColor("green");
  if(ImGui::Button("Add Column")){
    pulsated = true;
    printf("estoy en: %s\n", data_base.table_names[table].c_str());
    for(int k = 0 ; k < (int)data_base.column_names[table].size(); k ++) {
      if(strcmp(data_base.column_names[table][k].c_str(), creator.aux) != 0) {
        exist = true;
        pulsated = false;
        doitonce = true;
      }
    }
  }

  if(doitonce) {
    char sql_add_column[255] = {"\0"};
    strcat(sql_add_column, "ALTER TABLE ");
    strcat(sql_add_column, data_base.table_names[table].c_str());
    strcat(sql_add_column, " ADD COLUMN ");
    strcat(sql_add_column, creator.aux);
    strcat(sql_add_column, " VARCHAR");
    printf("SQL DELETE: %s\n", sql_add_column);
    handler = sqlite3_open(db_path, &db);
    handler = sqlite3_exec(db, sql_add_column, 0, 0, 0);
    memset(creator.aux,'\0',sizeof(creator.aux));
    FreeDB();
    initDB();
    doitonce = false;
  }
  DB_imgui.SetButtonColor("blue");

  ImGui::SameLine();
  if(ImGui::Button("Close")) {
    exist = false;
    pulsated = false;
    memset(creator.aux,'\0',sizeof(creator.aux));
    ImGui::CloseCurrentPopup();
  }

  if(exist && strlen(creator.aux) == 0) {
    ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Column added Succesfully :D");
  }else if (strlen(creator.aux) > 0) {
    exist = false;
  }

  if(pulsated && !exist) {
    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "This Column exists :/");
  }

  ImGui::EndPopup();
}

void Database::DeleteColumnPopUp(int table) {
  sqlite3* db = nullptr;
  ImGui::TextColored(ImVec4(0.0f,0.0f,1.0f,1.0f), "Insert the Name of the Table's Column that you want to delete");
  ImGui::InputText("Name of the Column", creator.aux, 25);

  static bool exist = false;
  static bool pulsated = false;
  DB_imgui.SetButtonColor("red");
  if(ImGui::Button("Delete Column")){
    pulsated = true;
    printf("Estoy en la tabla: %s\n", data_base.table_names[table].c_str());
    for(int k = 1 ; k < (int)data_base.column_names[table].size(); k++){
      if(strcmp(data_base.column_names[table][k].c_str(), creator.aux) == 0) {
        exist = true;
        pulsated = false;
        printf("Existe!!\n");
        strcpy((char*)creator.table_name.c_str(), "temporal");

        //Copiar el nombre de las columnas
        for(int s = 1 ; s < (int)data_base.column_names[table].size(); s++){
          if(strcmp(data_base.column_names[table][s].c_str(), creator.aux) != 0) {
            creator.column_names.push_back(data_base.column_names[table][s].c_str());
          }
        }
        char old_table_name[33] = "\0";
        char creator_deletation[33] = "\0";
        strcpy(creator_deletation, creator.aux);
        strcpy(old_table_name, data_base.table_names[table].c_str());
        CreateTable(db_path);
        FreeDB();
        initDB();

        int auxiliary = 0;
        int auxiliary2 = 0;

        //Copiar e insertar en la tabla temporal!!
        do {
          data_base.insert_values[(int)data_base.table_names.size() - 1].resize(0); //poner la mierda esta a 0 para poder meter las cosas bien
          for(int s = 0 ; s < (int)data_base.column_names[table].size(); s++){
            if(strcmp(data_base.column_names[table][s].c_str(), creator_deletation) != 0) {
              data_base.insert_values[(int)data_base.table_names.size() - 1].push_back(data_base.table_data[table][s + auxiliary].c_str());
            }
          }
          InsertDataBase(&data_base, db_path, (int)data_base.table_names.size() -1);
          FreeDB();
          initDB();
          auxiliary2 ++;
          if(auxiliary2 != (int)data_base.column_names[table].size()){
            auxiliary += (int)data_base.column_names[table].size();
          }
        }while (auxiliary != (int)data_base.table_data[table].size());

        //borrar la primera fila de la tabla temporal:
        char sql_delete[255] = {"\0"};
        strcat(sql_delete, "DELETE FROM temporal WHERE ID = 1");
        printf("SQL DELETE: %s\n", sql_delete);
        handler = sqlite3_open(db_path, &db);
        handler = sqlite3_exec(db, sql_delete, 0, 0, 0);
        FreeDB();
        initDB();

        char sql_drop_table[255] = {"\0"};
        strcat(sql_drop_table, "DROP TABLE ");
		    strcat(sql_drop_table, data_base.table_names[table].c_str());
        printf("SQL DESTROY: %s\n", sql_drop_table);
        handler = sqlite3_open(db_path, &db);
        handler = sqlite3_exec(db, sql_drop_table, 0, 0, 0);
        FreeDB();
        initDB();

        int division = ((int)data_base.table_data[(int)data_base.table_names.size() - 1].size() / (int)data_base.column_names[(int)data_base.table_names.size() - 1].size());
        for(int u = 0; u < division; u++) {
          char upt1[10] = "\0"; char upt2[10] = "\0";
          sprintf(upt1, "%d", (u + 1)); sprintf(upt2, "%d", (u + 2));
          char sql_update_id[255] = {"\0"};
          strcat(sql_update_id,"UPDATE temporal SET ID ='");
          strcat(sql_update_id, upt1);
          strcat(sql_update_id, "' WHERE ID = '");
          strcat(sql_update_id, upt2);
          strcat(sql_update_id, "';");
          printf("SQL UPDATE ID: %s\n", sql_update_id);
          handler = sqlite3_open(db_path, &db);
          handler = sqlite3_exec(db, sql_update_id, 0, 0, 0);
        }

        FreeDB();
        initDB();



        char sql_rename[255] = {"\0"};
        strcat(sql_rename, "ALTER TABLE temporal RENAME TO ");
        strcat(sql_rename, old_table_name);
        printf("SQL RENAME: %s\n", sql_rename);
        handler = sqlite3_open(db_path, &db);
        handler = sqlite3_exec(db, sql_rename, 0, 0, 0);

        FreeDB();
        initDB();

        //Limpiar el resto
        creator.table_name.clear();
        creator.column_names.clear();
        //printf("SQL DELETE: %s,\n", sql_delete);
      }
    }
  }
  DB_imgui.SetButtonColor("blue");

  ImGui::SameLine();
  if(ImGui::Button("Close")) {
    exist = false;
    pulsated = false;
    FreeDB();
    initDB();
    ImGui::CloseCurrentPopup();
  }

  if(exist && strlen(creator.aux) == 0) {
    ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Column deleted Succesfully :D");
  }else if (strlen(creator.aux) > 0) {
    exist = false;
  }

  if(pulsated && !exist) {
    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "The Column doesn't exists :/");
  }

  ImGui::EndPopup();
}

void Database::DeleteRowPopUp(databaseinfo *current_db, const char *path, int table) {
  sqlite3* db = nullptr;
  ImGui::TextColored(ImVec4(0.0f,0.0f,1.0f,1.0f), "Insert the ID of the Table's Row that you want to delete");
  ImGui::InputText("ID of the Row", creator.aux, 25);

  static bool exist = false;
  static bool pulsated = false;
  DB_imgui.SetButtonColor("red");
  if(ImGui::Button("Delete Row")){
    pulsated = true;
    printf("estoy en: %s\n", current_db->table_names[table].c_str());
    for(int k = 0 ; k < (int)current_db->table_data[table].size(); k += (int)current_db->column_names[table].size()){
      //printf("ID disponible: %s\n", (char*)current_db->table_data[table][k].c_str());
      if(strcmp(current_db->table_data[table][k].c_str(), creator.aux) == 0) {
        exist = true;
        pulsated = false;
        char sql_delete[255] = {"\0"};
        strcat(sql_delete, "DELETE FROM ");
			  strcat(sql_delete, current_db->table_names[table].c_str());
			  strcat(sql_delete, " WHERE ID");
			  strcat(sql_delete, " = ");
			  strcat(sql_delete, creator.aux);
			  strcat(sql_delete, "");
        handler = sqlite3_open(path, &db);
        handler = sqlite3_exec(db, sql_delete, 0, 0, 0);
        memset(creator.aux,'\0',sizeof(creator.aux));

        int division = ((int)current_db->table_data[(int)current_db->table_names.size() - 1].size() / (int)current_db->column_names[(int)current_db->table_names.size() - 1].size());
        for(int u = 0; u < division; u++) {
          char upt1[10] = "\0"; char upt2[10] = "\0";
          sprintf(upt1, "%d", (u + 1)); sprintf(upt2, "%d", (u + 2));
          char sql_update_id[255] = {"\0"};
          strcat(sql_update_id, "UPDATE ");
          strcat(sql_update_id, current_db->table_names[table].c_str());
          strcat(sql_update_id, " SET ID ='");
          strcat(sql_update_id, upt1);
          strcat(sql_update_id, "' WHERE ID = '");
          strcat(sql_update_id, upt2);
          strcat(sql_update_id, "';");
          printf("SQL UPDATE ID: %s\n", sql_update_id);
          handler = sqlite3_open(path, &db);
          handler = sqlite3_exec(db, sql_update_id, 0, 0, 0);
        }

        FreeDB();
        initDB();
      }
    }
  }
  DB_imgui.SetButtonColor("blue");

  ImGui::SameLine();
  if(ImGui::Button("Close")) {
    exist = false;
    pulsated = false;
    memset(creator.aux,'\0',sizeof(creator.aux));
    ImGui::CloseCurrentPopup();
  }

  if(exist && strlen(creator.aux) == 0) {
    ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "Row deleted Succesfully :D");
  }else if (strlen(creator.aux) > 0) {
    exist = false;
  }

  if(pulsated && !exist) {
    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "The Row doesn't exists :/");
  }

  ImGui::EndPopup();
}

//SHOW DATABASE
void Database::bottomButtonsDB() {
  unsigned int flag =  ImGuiWindowFlags_NoMove;
  ImVec2 cr = ImGui::GetWindowContentRegionMax();
  //DB_imgui.setPositionX(0);
  DB_imgui.SetButtonColor("green");
  if(ImGui::Button("CREATE A NEW NORMAL TABLE", ImVec2(cr.x * 0.488f, 30.0f))){
    ImGui::OpenPopup("Create a New Table");
  }
  DB_imgui.SetButtonColor("blue");
  if(ImGui::BeginPopupModal("Create a New Table",NULL,flag)){
    ImGui::SetWindowSize(ImVec2(400.0f, 300.0f));
    CreateTablePopUp();
  }
  ImGui::SameLine();
  DB_imgui.SetButtonColor("red");
  if(ImGui::Button("DELETE A NORMAL TABLE", ImVec2(cr.x * 0.488f, 30.0f))){
    ImGui::OpenPopup("Delete Table");
  }
  DB_imgui.SetButtonColor("blue");
  if(ImGui::BeginPopupModal("Delete Table",NULL,flag)){
    ImGui::SetWindowSize(ImVec2(400.0f, 300.0f));
    DestroyTablePopUp();
  }
}

void Database::bottomButtonsBirthdayDB() {
  ImVec2 cr = ImGui::GetWindowContentRegionMax();
  //DB_imgui.setPositionX(0);
  static bool pulsated_c = false;
  static bool pulsated_d = false;
  static bool created = false;
  static bool deleted = false;
  static bool popup = false;
  DB_imgui.SetButtonColor("green");
  if(ImGui::Button("CREATE THE BIRTHDAY TABLE", ImVec2(cr.x * 0.488f, 30.0f))) {
    pulsated_d = false;
    pulsated_c = true;
    if((int)birthday_db.table_names.size() == 0) {
      strcpy((char*)creator.table_name.c_str(), "Birthdays");
      creator.column_names.push_back("Name");
      creator.column_names.push_back("Day");
      creator.column_names.push_back("Month");
      creator.column_names.push_back("Year");
      creator.column_names.push_back("Created");
      CreateTable(birthday_db_path);
      creator.table_name.clear();
      creator.column_names.clear();
      FreeDB();
      initDB();
      created = true;
    } else {
      created = false;
    }
  }
  ImGui::SameLine();
  DB_imgui.SetButtonColor("red");
  if(ImGui::Button("DELETE THE BIRTHDAY TABLE", ImVec2(cr.x * 0.488f, 30.0f))) {
    pulsated_c = false;
    pulsated_d = true;
    if((int)birthday_db.table_names.size() > 0) {
      popup = true;
      ImGui::OpenPopup("DELETE?");
    }else if ((int)birthday_db.table_names.size() == 0){
        deleted = false;
    }
  }

  ImVec2 center = ImGui::GetMainViewport()->GetCenter();
  ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
  static bool dont_ask_me_next_time = false;
  if(ImGui::BeginPopupModal("DELETE?", NULL, ImGuiWindowFlags_NoMove)) {
    ImGui::SetWindowSize(ImVec2(400.0f, 165.0f));
    DB_imgui.addSpace(2);
    DB_imgui.setPositionX(20.0f);
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.20f, 0.75f),"ALL THOSE USERS AND ITS BIRTHDAYS WILL BE DELETED :c\n");
    DB_imgui.addSpace(1);
    DB_imgui.setPositionX(100.0f);
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.20f, 0.75f),"THIS OPERATION CANNOT BE UNDONE!!\n\n");
    ImGui::Separator();

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    DB_imgui.SetInputColor("blue");
    ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
    DB_imgui.SetInputColor("gray");
    ImGui::PopStyleVar();

    if (ImGui::Button("OK", ImVec2(120, 0))) {
      sqlite3* db;
      char sql_drop_table[255] = {"\0"};
      strcat(sql_drop_table, "DROP TABLE Birthdays");
      printf("SQL DESTROY: %s\n", sql_drop_table);
      handler = sqlite3_open(birthday_db_path, &db);
      handler = sqlite3_exec(db, sql_drop_table, 0, 0, 0);
      FreeDB();
      initDB();
      deleted = true;
      popup = false;
      ImGui::CloseCurrentPopup();
    }
      ImGui::SetItemDefaultFocus();
      ImGui::SameLine();
    DB_imgui.SetButtonColor("blue");
    if (ImGui::Button("Cancel", ImVec2(120, 0))) {
      pulsated_d = false;
      popup = false;
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }

  DB_imgui.SetButtonColor("blue");
  if(pulsated_c && created){
    DB_imgui.setPositionX(cr.x * 0.35f);
    ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "BIRTHDAYS TABLE CREATED SUCCESFULLY :D");
  }else if(pulsated_c && !created) {
    DB_imgui.setPositionX(cr.x * 0.35f);
    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "BIRTHDAYS TABLE ALREADY EXISTS!! :p");
  }
  if(pulsated_d && deleted &&!popup){
    DB_imgui.setPositionX(cr.x * 0.35f);
    ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "BIRTHDAYS TABLE DELETED SUCCESFULLY :D");
  }else if(pulsated_d && !deleted &&!popup) {
    DB_imgui.setPositionX(cr.x * 0.35f);
    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "BIRTHDAYS TABLE DOESN'T EXISTS!! :p");
  }
}

void Database::DataBaseImGui(){ //NO TOCAR ESTE CONYO
  unsigned int flag =  ImGuiWindowFlags_NoMove;
  ImVec2 cr = ImGui::GetWindowContentRegionMax();
  ImVec2 cr_aux;
  ImVec2 cr_table;
  static bool display = false;
  static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg; //ImGuiTableFlags_Resizable no me gusta del todo

  DB_imgui.setPositionX(cr.x * 0.45f);
  ImGui::TextColored(ImVec4(0.0f,1.0f,1.0f,1.0f), "NORMAL TABLES:");

  /*

  DB_imgui.SetInputColor("gray");
  for (int n = 0; n < rows; n++) {
    char buf[100] = "\0";
    strcat(buf, birthday_db.table_data[0][(6 * n)].c_str()); //ID
    strcat(buf, ": ");
    strcat(buf, birthday_db.table_data[0][1 + (6 * n)].c_str()); //Nombre
    if (filter.PassFilter(buf)) {
      bool open = ImGui::CollapsingHeader(buf);
      if (open && ImGui::BeginTable("Table", 2, flags)) {
  */

  static ImGuiTextFilter filter;

  DB_imgui.SetInputColor("blue");
  for(int i = 0 ; i < (int)data_base.table_names.size() ;++i){
    if(ImGui::CollapsingHeader(data_base.table_names[i].c_str()) &&  data_base.column_names[i].capacity() != 0) {
      filter.Draw("WRITE HERE WHAT YOU ARE LOOKING FOR", 200.0f); //new
      if (ImGui::BeginTable(data_base.table_names[i].c_str(),data_base.column_names[i].size(), flags)){
        for(int cell = 0; cell < (int)data_base.column_names[i].size(); cell++){
          ImGui::TableSetupColumn(data_base.column_names[i][cell].c_str());
        }
          ImGui::TableHeadersRow();
        for (int cell = 0; cell <  (int)data_base.table_data[i].size(); cell++){

            ImGui::TableNextColumn();
            char tmp[5] = "\0\0\0\0";
            sprintf(tmp, "##%d\0", cell);
            cr_table = ImGui::GetWindowContentRegionMax();
            float size = (1 / (float)data_base.column_names[i].size());
            ImGui::PushItemWidth(cr_table.x * size * 0.95f);
            DB_imgui.SetButtonColor("gray");
            if(cell%(int)data_base.column_names[i].size() == 0){
               ImGui::Button((char *)data_base.table_data[i][cell].c_str(), ImVec2(-FLT_MIN, 0.0f));
            }else{
              ImGui::InputText(tmp,(char *)data_base.table_data[i][cell].c_str(), 21);
            }
            DB_imgui.SetButtonColor("blue");
        }
        ImGui::TableNextColumn();

        DB_imgui.SetHeaderColor("blue");
        DB_imgui.SetInputColor("green");
        if(ImGui::CollapsingHeader("Insert Values")){
          display = true;
          cr_aux = ImGui::GetWindowContentRegionMax();
          for(int k = 1 ; k < (int)data_base.column_names[i].size() ; ++k){
            ImGui::TableNextColumn();
            char tmp2[35] = "\0";
            memset(tmp2,'\0',sizeof(tmp2));
            sprintf(tmp2, "##insert%d\0", k);
            ImGui::InputText(tmp2,(char *)data_base.insert_values[i][k].data(), 21);
          }
        }else{
          display = false;
        }
        DB_imgui.SetHeaderColor("gray");
        DB_imgui.SetInputColor("blue");

        ImGui::EndTable();
        if(display) {
          ImVec2 w_pos_aux = ImGui::GetCursorPos();
          ImGui::SetCursorPos(ImVec2(cr_aux.x * 0.25f, w_pos_aux.y));
          DB_imgui.SetButtonColor("green");
          if(ImGui::Button("INSERT THE NEW DATA", ImVec2(cr_aux.x * 0.5f, 20.0f))){
            InsertDataBase(&data_base, db_path, i);
            for(int k = 1 ; k < (int)data_base.column_names[i].size() ; ++k){
              data_base.insert_values[i][k].clear(); //limpiar despues de meter
            }
          }
          DB_imgui.SetButtonColor("blue");
        }


        DB_imgui.addSpace(1);

        char tmp_table[5] = "\0";
        char act_row[33] = "\0";
        char act_col[33] = "\0";
        char new_col[33] = "\0";
        strcpy(act_row, "Delete a Row");
        strcpy(act_col, "Delete a Column");
        strcpy(new_col, "Add a Column");
        sprintf(tmp_table, "##%d\0", i);
        strcat(act_row, tmp_table);
        strcat(act_col, tmp_table);
        strcat(new_col, tmp_table);

        float button_w  = (1.0f/4.210f);
        if(ImGui::Button("Update", ImVec2(cr.x * button_w, 20.0f))){
          SaveDataBase(&data_base, db_path);
          UpdateAuxData(&data_base);
        }

        ImGui::SameLine();
        DB_imgui.setPositionX((cr.x * button_w) + 20.0f);
        DB_imgui.SetButtonColor("red");
        if(ImGui::Button(act_row, ImVec2(cr.x * button_w, 20.0f))){
          ImGui::OpenPopup(act_row);
        }

        ImGui::SameLine();
        DB_imgui.setPositionX((cr.x * (button_w * 2.0f)) + 32.0f);
        if(ImGui::Button(act_col, ImVec2(cr.x * button_w, 20.0f))){
          ImGui::OpenPopup(act_col);
        }

        ImGui::SameLine();
        DB_imgui.SetButtonColor("green");
        DB_imgui.setPositionX((cr.x * (button_w * 3.0f)) + 44.0f);
        if(ImGui::Button(new_col, ImVec2(cr.x * button_w, 20.0f))){
        ImGui::OpenPopup(new_col);
        }
        DB_imgui.SetButtonColor("blue");

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if(ImGui::BeginPopupModal(act_row,NULL,flag)){
          ImGui::SetWindowSize(ImVec2(500.0f, 300.0f));
          DeleteRowPopUp(&data_base, db_path, i);
        }

        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if(ImGui::BeginPopupModal(act_col,NULL,flag)){
          ImGui::SetWindowSize(ImVec2(500.0f, 300.0f));
          DeleteColumnPopUp(i);
        }

        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if(ImGui::BeginPopupModal(new_col,NULL,flag)){
          ImGui::SetWindowSize(ImVec2(500.0f, 300.0f));
          AddColumnPopUp(i);
        }

        if(i < (int)data_base.table_names.size() - 1) {
          DB_imgui.addSpace(3);
          DB_imgui.addSeparator(2);
          DB_imgui.addSpace(3);
        }
      }
    }else if(data_base.column_names[i].capacity() == 0){
      ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "EMPTY TABLE");
    }

  }
  DB_imgui.addSpace(3);
  DB_imgui.addSeparator(2);
  DB_imgui.addSpace(3);

  //botones de abajo
  bottomButtonsDB();
}

void Database::ImGuiColorChanger(){
  /*unsigned int flag =  ImGuiWindowFlags_NoMove;
  ImVec2 cr = ImGui::GetWindowContentRegionMax();
  ImVec2 cr_aux;
  ImVec2 cr_table;
  static bool display = false;
  static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg; //ImGuiTableFlags_Resizable no me gusta del todo

  DB_imgui.setPositionX(cr.x * 0.45f);
  ImGui::TextColored(ImVec4(0.0f,1.0f,1.0f,1.0f), "IMGUI STYLES:");

  DB_imgui.SetInputColor("blue");
  for(int i = 0 ; i < (int)color_db.table_names.size() ;++i){

    if(ImGui::CollapsingHeader(color_db.table_names[i].c_str()) &&  color_db.column_names[i].capacity() != 0) {
      if (ImGui::BeginTable(color_db.table_names[i].c_str(),color_db.column_names[i].size(), flags)){
        for(int cell = 0; cell < (int)color_db.column_names[i].size(); cell++){
          ImGui::TableSetupColumn(color_db.column_names[i][cell].c_str());
        }
          ImGui::TableHeadersRow();
        for (int cell = 0; cell <  (int)color_db.table_data[i].size(); cell++){
            ImGui::TableNextColumn();
            char tmp[5] = "\0\0\0\0";
            sprintf(tmp, "##%d\0", cell);
            cr_table = ImGui::GetWindowContentRegionMax();
            float size = (1 / (float)color_db.column_names[i].size());
            ImGui::PushItemWidth(cr_table.x * size * 0.95f);
            DB_imgui.SetButtonColor("gray");
            if(cell%(int)color_db.column_names[i].size() == 0){
               ImGui::Button((char *)color_db.table_data[i][cell].c_str(), ImVec2(-FLT_MIN, 0.0f));
            }else {
              ImGui::InputText(tmp,(char *)color_db.table_data[i][cell].c_str(), 21);
            }
            DB_imgui.SetButtonColor("blue");
        }
        ImGui::TableNextColumn();

        DB_imgui.SetHeaderColor("blue");
        DB_imgui.SetInputColor("green");
        if(ImGui::CollapsingHeader("Insert Values")){
          display = true;
          cr_aux = ImGui::GetWindowContentRegionMax();
          for(int k = 1 ; k < (int)color_db.column_names[i].size() ; ++k){
            ImGui::TableNextColumn();
            char tmp2[35] = "\0";
            memset(tmp2,'\0',sizeof(tmp2));
            sprintf(tmp2, "##insert%d\0", k);
            ImGui::InputText(tmp2,(char *)color_db.insert_values[i][k].data(), 21);
          }
        }else{
          display = false;
        }
        DB_imgui.SetHeaderColor("gray");
        DB_imgui.SetInputColor("blue");

        ImGui::EndTable();
        if(display) {
          ImVec2 w_pos_aux = ImGui::GetCursorPos();
          ImGui::SetCursorPos(ImVec2(cr_aux.x * 0.25f, w_pos_aux.y));
          DB_imgui.SetButtonColor("green");
          if(ImGui::Button("INSERT THE NEW DATA", ImVec2(cr_aux.x * 0.5f, 20.0f))){
            InsertDataBase(&color_db, styles_db_path, i);
            for(int k = 1 ; k < (int)color_db.column_names[i].size() ; ++k){
              color_db.insert_values[i][k].clear(); //limpiar despues de meter
            }
          }
          DB_imgui.SetButtonColor("blue");
        }


        DB_imgui.addSpace(1);

        char tmp_table[5] = "\0";
        char act_row[33] = "\0";
        char act_col[33] = "\0";
        char new_col[33] = "\0";
        strcpy(act_row, "Delete a Row");
        strcpy(act_col, "Delete a Column");
        strcpy(new_col, "Add a Column");
        sprintf(tmp_table, "##%d\0", i);
        strcat(act_row, tmp_table);
        strcat(act_col, tmp_table);
        strcat(new_col, tmp_table);

        float button_w  = (1.0f/4.210f);
        if(ImGui::Button("Update", ImVec2(cr.x * button_w, 20.0f))){
          SaveDataBase(&color_db, styles_db_path);  //done
          UpdateAuxData(&color_db);
        }

        ImGui::SameLine();
        DB_imgui.setPositionX((cr.x * button_w) + 20.0f);
        DB_imgui.SetButtonColor("red");
        if(ImGui::Button(act_row, ImVec2(cr.x * button_w, 20.0f))){
          ImGui::OpenPopup(act_row);
        }

        ImGui::SameLine();
        DB_imgui.setPositionX((cr.x * (button_w * 2.0f)) + 32.0f);
        if(ImGui::Button(act_col, ImVec2(cr.x * button_w, 20.0f))){
          ImGui::OpenPopup(act_col);
        }

        ImGui::SameLine();
        DB_imgui.SetButtonColor("green");
        DB_imgui.setPositionX((cr.x * (button_w * 3.0f)) + 44.0f);
        if(ImGui::Button(new_col, ImVec2(cr.x * button_w, 20.0f))){
        ImGui::OpenPopup(new_col);
        }
        DB_imgui.SetButtonColor("blue");

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if(ImGui::BeginPopupModal(act_row,NULL,flag)){
          ImGui::SetWindowSize(ImVec2(500.0f, 300.0f));
          DeleteRowPopUp(&color_db, styles_db_path, i);   //done
        }

        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if(ImGui::BeginPopupModal(act_col,NULL,flag)){
          ImGui::SetWindowSize(ImVec2(500.0f, 300.0f));
          DeleteColumnPopUp(i);
        }

        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if(ImGui::BeginPopupModal(new_col,NULL,flag)){
          ImGui::SetWindowSize(ImVec2(500.0f, 300.0f));
          AddColumnPopUp(i);
        }

        if(i < (int)color_db.table_names.size() - 1) {
          DB_imgui.addSpace(3);
          DB_imgui.addSeparator(2);
          DB_imgui.addSpace(3);
        }
      }
    }else if(color_db.column_names[i].capacity() == 0){
      ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "EMPTY TABLE");
    }

  }
  DB_imgui.addSpace(3);
  DB_imgui.addSeparator(2);
  DB_imgui.addSpace(3);*/



      ImGuiStyle& style = ImGui::GetStyle();

      static int output_dest = 0;
      static bool output_only_modified = true;


      //ImGui::SameLine(); ImGui::SetNextItemWidth(120); ImGui::Combo("##output_type", &output_dest, "To Clipboard\0To TTY\0");
      ImGui::Checkbox("Only Modified Colors", &output_only_modified);

      static ImGuiTextFilter filter;
      filter.Draw("Filter colors", ImGui::GetFontSize() * 16);

      static ImGuiColorEditFlags alpha_flags = 0;
      if (ImGui::RadioButton("Opaque", alpha_flags == ImGuiColorEditFlags_None))             { alpha_flags = ImGuiColorEditFlags_None; } ImGui::SameLine();
      if (ImGui::RadioButton("Alpha",  alpha_flags == ImGuiColorEditFlags_AlphaPreview))     { alpha_flags = ImGuiColorEditFlags_AlphaPreview; } ImGui::SameLine();
      if (ImGui::RadioButton("Both",   alpha_flags == ImGuiColorEditFlags_AlphaPreviewHalf)) { alpha_flags = ImGuiColorEditFlags_AlphaPreviewHalf; }

      ImGui::BeginChild("##colors", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
      ImGui::PushItemWidth(-160);
      for (int i = 0; i < ImGuiCol_COUNT; i++)
      {
          const char* name = ImGui::GetStyleColorName(i);
          if (!filter.PassFilter(name))
              continue;
          ImGui::PushID(i);
          ImGui::ColorEdit4("##color", (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);

          ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
          ImGui::TextUnformatted(name);
          ImGui::PopID();
      }


      //Vuelve Aqui:
      if(ImGui::Button("Save Style", ImVec2(-FLT_MIN, 0.0f))){
        for (int i = 0; i < ImGuiCol_COUNT; i++) {
          const char* name = ImGui::GetStyleColorName(i);
          ImGui::PushID(i);
          ImGui::ColorEdit4("##color", (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);

          ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
          ImGui::TextUnformatted(name);
          ImGui::PopID();
        }
      }


      ImGui::PopItemWidth();
      ImGui::EndChild();


}

//FREE DATABASE
void Database::FreeDB(){
  for(int i = 0 ; i < (int)data_base.table_names.size() ;i++ ){
    data_base.table_data[i].clear();
    data_base.aux_data[i].clear();
    data_base.column_names[i].clear();
    data_base.selectedMonth[i].clear();
    data_base.selectedDay[i].clear();
  }
  data_base.table_names.clear();

  for(int i = 0 ; i < (int)birthday_db.table_names.size() ;i++ ){
    birthday_db.table_data[i].clear();
    birthday_db.aux_data[i].clear();
    birthday_db.column_names[i].clear();
    birthday_db.selectedMonth[i].clear();
    birthday_db.selectedDay[i].clear();
  }
  birthday_db.table_names.clear();

  for(int i = 0 ; i < (int)color_db.table_names.size() ;i++ ){
    color_db.table_data[i].clear();
    color_db.aux_data[i].clear();
    color_db.column_names[i].clear();
    color_db.selectedMonth[i].clear();
    color_db.selectedDay[i].clear();
  }
  color_db.table_names.clear();

  delete[] data_base.column_names;
  delete[] data_base.table_data;
  delete[] data_base.aux_data;
  delete[] data_base.selectedMonth;
  delete[] data_base.selectedDay;

  delete[] birthday_db.column_names;
  delete[] birthday_db.table_data;
  delete[] birthday_db.aux_data;
  delete[] birthday_db.selectedMonth;
  delete[] birthday_db.selectedDay;

  delete[] color_db.column_names;
  delete[] color_db.table_data;
  delete[] color_db.aux_data;
  delete[] color_db.selectedMonth;
  delete[] color_db.selectedDay;

  printf("\nMemory Free process from the database done succesfully\n");
}

/*-------------BIRTHDAY DATABASE-------------*/

//SHOW BIRTHDAY TABLES
void Database::BirthdayDataBaseImGui() {
  unsigned int flag =  ImGuiWindowFlags_NoMove;
  ImVec2 cr = ImGui::GetWindowContentRegionMax();
  ImVec2 cr_aux;
  ImVec2 cr_table;
  static bool display = false;
  static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg ;

  static int selectedD = 0;
  static int selectedM = 0;

  DB_imgui.setPositionX(cr.x * 0.45f);
  ImGui::TextColored(ImVec4(0.0f,1.0f,1.0f,1.0f), "BIRTHDAY TABLE:");
  int auxD = 1;
  int auxM = 1;

  DB_imgui.SetInputColor("blue");
  for(int i = 0 ; i < (int)birthday_db.table_names.size() ;++i){

    if(ImGui::CollapsingHeader(birthday_db.table_names[i].c_str()) &&  birthday_db.column_names[i].capacity() != 0) {
      if (ImGui::BeginTable(birthday_db.table_names[i].c_str(),birthday_db.column_names[i].size(), flags)){
        for(int cell = 0; cell < (int)birthday_db.column_names[i].size(); cell++){
          ImGui::TableSetupColumn(birthday_db.column_names[i][cell].c_str());
        }
          ImGui::TableHeadersRow();
        for (int cell = 0; cell <  (int)birthday_db.table_data[i].size(); cell++){
            ImGui::TableNextColumn();
            char tmp[5] = "\0\0\0\0";
            sprintf(tmp, "##%d\0", cell);
            cr_table = ImGui::GetWindowContentRegionMax();
            float size = (1 / (float)birthday_db.column_names[i].size());
            ImGui::PushItemWidth(cr_table.x * size * 0.95f);
            DB_imgui.SetButtonColor("gray");
            int result = cell%(int)birthday_db.column_names[i].size();
            switch(result) {
              case 0: ImGui::Button((char *)birthday_db.table_data[i][cell].c_str(), ImVec2(-FLT_MIN, 0.0f));
              break;
              case 1: ImGui::InputText(tmp,(char *)birthday_db.table_data[i][cell].c_str(), 20);
              break;
              case 2: //ImGui::InputText(tmp,(char *)birthday_db.table_data[i][cell].c_str(), 3);
                if(auxD < (int)birthday_db.selectedDay[i].size() + 1){
                  int aux_result;
                  if(auxD == 1){
                    aux_result = (cell - result);
                  }else{
                    aux_result = (cell - result);
                    aux_result = (aux_result/6);
                  }
                  ImGui::Combo(tmp, &birthday_db.selectedDay[i][aux_result], daysItems, IM_ARRAYSIZE(daysItems));
                  strcpy((char *)birthday_db.table_data[i][cell].c_str(), daysItems[birthday_db.selectedDay[i][aux_result]]);
                  auxD ++;
                }
              break;
              case 3:
                if(auxM < (int)birthday_db.selectedMonth[i].size() + 1){
                  int aux_result;
                  if(auxM == 1){
                    aux_result = (cell - (result * auxM));
                  }else{
                    aux_result = (cell - (result * auxM));
                    aux_result = (aux_result/result);
                  }
                  ImGui::Combo(tmp, &birthday_db.selectedMonth[i][aux_result], monthsItems, IM_ARRAYSIZE(monthsItems));
                  strcpy((char *)birthday_db.table_data[i][cell].c_str(), monthsItems[birthday_db.selectedMonth[i][aux_result]]);
                  auxM ++;
                }
              break;
              case 4: ImGui::InputText(tmp,(char *)birthday_db.table_data[i][cell].c_str(), 5);
              break;
              case 5: ImGui::Button((char *)birthday_db.table_data[i][cell].c_str(), ImVec2(-FLT_MIN, 0.0f));
              break;
            }
            DB_imgui.SetButtonColor("blue");
        }
        ImGui::TableNextColumn();

        DB_imgui.SetHeaderColor("blue");
        DB_imgui.SetInputColor("green");
        if(ImGui::CollapsingHeader("Insert Values")){
          display = true;
          cr_aux = ImGui::GetWindowContentRegionMax();
          for(int k = 1 ; k < (int)birthday_db.column_names[i].size() ; ++k){
            ImGui::TableNextColumn();
            char tmp2[20] = "\0";
            memset(tmp2,'\0',sizeof(tmp2));
            sprintf(tmp2, "##insert%d\0", k);
            switch(k) {
              case 1: ImGui::InputText(tmp2,(char *)birthday_db.insert_values[i][k].c_str(), 20);
              break;
              case 2: ImGui::Combo(tmp2, &selectedD, daysItems, IM_ARRAYSIZE(daysItems));
                      strcpy((char*)birthday_db.insert_values[i][k].c_str(), daysItems[selectedD]);
              break;
              case 3: ImGui::Combo(tmp2, &selectedM, monthsItems, IM_ARRAYSIZE(monthsItems));
                      strcpy((char*)birthday_db.insert_values[i][k].c_str(), monthsItems[selectedM]);
              break;
              case 5: ImGui::Text((char *)birthday_db.insert_values[i][k].c_str());
              break;
              case 4: ImGui::InputText(tmp2,(char *)birthday_db.insert_values[i][k].c_str(), 5);
              break;
              default: ImGui::InputText(tmp2,(char *)birthday_db.insert_values[i][k].c_str(), 20);
              break;
            }
          }
        }else{
          display = false;
        }
        ImGui::EndTable();
        DB_imgui.SetHeaderColor("gray");
        DB_imgui.SetInputColor("gray");

        if(display) {
          ImVec2 w_pos_aux = ImGui::GetCursorPos();
          ImGui::SetCursorPos(ImVec2(cr_aux.x * 0.25f, w_pos_aux.y));
          DB_imgui.SetButtonColor("green");
          if(ImGui::Button("INSERT THE NEW USER", ImVec2(cr_aux.x * 0.5f, 20.0f))){
            InsertBirthdayDataBase(i);
            for(int k = 1 ; k < (int)birthday_db.column_names[i].size(); ++k){
              birthday_db.insert_values[i][k].clear(); //limpiar despues de meter
            }
            selectedM = 0; selectedD = 0;
            FreeDB();
            initDB();
          }
          DB_imgui.SetButtonColor("blue");
        }

        char tmp_table[5] = "\0";
        char act_row[33] = "\0";
        strcpy(act_row, "Delete a Row");
        sprintf(tmp_table, "##%d\0", i);
        strcat(act_row, tmp_table);

        DB_imgui.addSpace(1);

        float button_w  = (1.0f/2.045f);
        if(ImGui::Button("Update", ImVec2(cr.x * button_w, 20.0f))){
          SaveDataBase(&birthday_db, birthday_db_path);
          UpdateAuxData(&birthday_db);
        }

        ImGui::SameLine();
        DB_imgui.setPositionX((cr.x * button_w) + 20.0f);
        DB_imgui.SetButtonColor("red");
        if(ImGui::Button(act_row, ImVec2(cr.x * button_w, 20.0f))){
          ImGui::OpenPopup(act_row);
        }

        if(ImGui::BeginPopupModal(act_row,NULL,flag)){
          ImGui::SetWindowSize(ImVec2(500.0f, 300.0f));
          DeleteRowPopUp(&birthday_db, birthday_db_path, i);
        }
      }
    }else if(birthday_db.column_names[i].capacity() == 0){
      ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "THE BIRTHDAY TABLE IS EMPTY. PLEASE, DELETE THIS TABLE AND CREATE ANOTHER ONE");
    }

  }
  DB_imgui.addSpace(3);
  DB_imgui.addSeparator(2);
  DB_imgui.addSpace(3);

  //botones de abajo
  bottomButtonsBirthdayDB();
}

//INSERT INTO THE DATABASE
int Database::InsertBirthdayDataBase(int table){
  sqlite3* db = nullptr;
  char tmp[5];
  int tmp2 = birthday_db.table_data[table].size()/birthday_db.column_names[table].size() + 1;
  sprintf(tmp,"%d",tmp2);
  //_____________________TABLE 1
  char sql[1024];
  memset(sql,'\0',sizeof(sql));

  strcat(sql,"INSERT INTO ");
  strcat(sql,birthday_db.table_names[table].c_str());
  strcat(sql," (");
  for(int i = 0 ; i < (int)birthday_db.column_names[table].size();i++){
    strcat(sql,birthday_db.column_names[table][i].c_str());
    if(i < (int)birthday_db.column_names[table].size()-1)
      strcat(sql,",");
  }
  strcat(sql,") VALUES ('");
  strcat(sql,tmp);
  strcat(sql,"'");
  strcat(sql,",");
  DB_clock.updateTimerClock();
  for(int i = 1 ; i < (int)birthday_db.insert_values[table].size();i++){
    if(i == (int)birthday_db.insert_values[table].size() -1) {
      strcat(sql,"'");
      strcat(sql, DB_clock.getTotalDate());
      strcat(sql, " ");
      strcat(sql, DB_clock.getHourString());
      strcat(sql, ":");
      strcat(sql, DB_clock.getMinuteString());
      strcat(sql, ":");
      strcat(sql, DB_clock.getSecondString());
      strcat(sql,"'");
    }else{
      strcat(sql,"'");
      strcat(sql,birthday_db.insert_values[table][i].c_str());
      strcat(sql,"'");
    }
    if(i < (int)birthday_db.insert_values[table].size()-1)
      strcat(sql,",");
  }//

  strcat(sql,");");

  for(int i = 0; i < (int)birthday_db.insert_values[table].size() ; i++){
    if( i == 0 ){
      birthday_db.table_data[table].push_back(tmp);
    }else{
      birthday_db.table_data[table].push_back(birthday_db.insert_values[table][i]);
    }
  }
  UpdateAuxData(&birthday_db);

  if(sql != NULL){
    handler = sqlite3_open(birthday_db_path, &db);
    handler = sqlite3_exec(db, sql, NULL, (void *)&birthday_db, 0);
    printf("%s\n", sql);
  }

  if (handler != SQLITE_OK) {
    printf("\n\tError executing SQL sentence!! 10\n");
    sqlite3_close(db);
    return 1;
  }

  sqlite3_close(db);
  return 0;
}

//SHOW ALL USERS OF THE DATABASE
void Database::BirthdayUsers() {

  const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;
  unsigned int flags = flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;


  ImGui::SetNextItemOpen(true, ImGuiCond_Once);

  ImGuiStyle * style = &ImGui::GetStyle();
  style->Colors[ImGuiCol_Text] = ImVec4(0.0f,0.65f,0.84f,1.0f);
  if(birthday_db.table_names.capacity() > 0 && (int)birthday_db.table_names.size() > 0) {
    if (ImGui::TreeNode("BIRTHDAY USERS")) {
      int rows = 0;
      if ((int)birthday_db.column_names[0].size() != 0) {
        rows = ((int)birthday_db.table_data[0].size() / (int)birthday_db.column_names[0].size());
      }
      style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
      static ImGuiTextFilter filter;
      DB_imgui.SetInputColor("blue");
      filter.Draw("WRITE HERE THE USER THAT YOU ARE LOOKING FOR", 200.0f);
      DB_imgui.SetInputColor("gray");
      for (int n = 0; n < rows; n++) {
        char buf[100] = "\0";
        strcat(buf, birthday_db.table_data[0][(6 * n)].c_str()); //ID
        strcat(buf, ": ");
        strcat(buf, birthday_db.table_data[0][1 + (6 * n)].c_str()); //Nombre
        if (filter.PassFilter(buf)) {
          bool open = ImGui::CollapsingHeader(buf);
          if (open && ImGui::BeginTable("Table", 2, flags)) {
            ImGui::TableSetupColumn("QUESTION", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 33.0f);
            ImGui::TableSetupColumn("ANSWER", ImGuiTableColumnFlags_NoHide);
            ImGui::TableHeadersRow();
            for (int cell = 0; cell < 28; cell++) {
              ImGui::TableNextColumn();
              if(cell%2 == 0) {
                DB_imgui.SetButtonColor("gray");
                switch(cell) {
                  case 0: ImGui::Button("TOTAL AGE:", ImVec2(-FLT_MIN, 0.0f)); //done
                  break;
                  case 2: ImGui::Button("BORN WEEK DAY:", ImVec2(-FLT_MIN, 0.0f));
                  break;
                  case 4: ImGui::Button("ZODIAC SIGN:", ImVec2(-FLT_MIN, 0.0f));
                  break;
                  case 6: ImGui::Button("MONTHS OLD:", ImVec2(-FLT_MIN, 0.0f));
                  break;
                  case 8: ImGui::Button("DAYS OLD:", ImVec2(-FLT_MIN, 0.0f));
                  break;
                  case 10: ImGui::Button("HOURS OLD:", ImVec2(-FLT_MIN, 0.0f));
                  break;
                  case 12: ImGui::Button("MINUTES OLD:", ImVec2(-FLT_MIN, 0.0f));
                  break;
                  case 14: ImGui::Button("SECONDS OLD:", ImVec2(-FLT_MIN, 0.0f));
                  break;
                  case 16: ImGui::Button("TOTAL TIME UNTIL NEXT BIRTHDAY:", ImVec2(-FLT_MIN, 0.0f));
                  break;
                  case 18: ImGui::Button("NEXT BIRTHDAY WEEK DAY:", ImVec2(-FLT_MIN, 0.0f));
                  break;
                  case 20: ImGui::Button("DAYS UNTIL BIRTHDAY:", ImVec2(-FLT_MIN, 0.0f));
                  break;
                  case 22: ImGui::Button("HOURS UNTIL BIRTHDAY:", ImVec2(-FLT_MIN, 0.0f));
                  break;
                  case 24: ImGui::Button("MINUTES UNTIL BIRTHDAY:", ImVec2(-FLT_MIN, 0.0f));
                  break;
                  case 26: ImGui::Button("SECONDS UNTIL BIRTHDAY:", ImVec2(-FLT_MIN, 0.0f));
                  break;
                }
                DB_imgui.SetButtonColor("blue");
              }else{
                switch(cell) {
                  case 1: ImGui::Text("%d YEARS,", DB_clock.getTotalAge(&birthday_db, n, "year")); ImGui::SameLine();
                  ImGui::Text("%d MONTHS AND", DB_clock.getTotalAge(&birthday_db, n, "month")); ImGui::SameLine();
                  ImGui::Text("%d DAYS OLD", DB_clock.getTotalAge(&birthday_db, n, "day"));
                  break;
                  case 3: ImGui::Text("WAS BORN ON A %s", DB_clock.getWeekDay(&birthday_db, n).c_str());
                  break;
                  case 5: ImGui::Text("%s", DB_clock.getZodiacName(&birthday_db, n).c_str());
                  break;
                  case 7: ImGui::Text("%0.2f MONTHS OLD", DB_clock.getTotalMonthsLived(&birthday_db, n));
                  break;
                  case 9: ImGui::Text("%d DAYS OLD", DB_clock.getTotalDaysLived(&birthday_db, n));
                  break;
                  case 11: ImGui::Text("%d HOURS OLD", DB_clock.getTotalHoursLived(DB_clock.getTotalDaysLived(&birthday_db, n)));
                  break;
                  case 13: ImGui::Text("%d MINUTES OLD", DB_clock.getTotalMinutesLived(DB_clock.getTotalHoursLived(DB_clock.getTotalDaysLived(&birthday_db, n))));
                  break;
                  case 15: ImGui::Text("%lu SECONDS OLD", DB_clock.getTotalSecondsLived(DB_clock.getTotalMinutesLived(DB_clock.getTotalHoursLived(DB_clock.getTotalDaysLived(&birthday_db, n)))));
                  break;
                  case 17: ImGui::Text("%d MONTHS,", DB_clock.getNextBirthday(&birthday_db, n, "month")); ImGui::SameLine();
                  ImGui::Text("%d DAYS,", DB_clock.getNextBirthday(&birthday_db, n, "day")); ImGui::SameLine();
                  ImGui::Text("%d HOURS,", DB_clock.getNextBirthday(&birthday_db, n, "hour")); ImGui::SameLine();
                  ImGui::Text("%d MINUTES AND", DB_clock.getNextBirthday(&birthday_db, n, "minute")); ImGui::SameLine();
                  ImGui::Text("%d SECONDS UNTIL BIRTHDAY :D", DB_clock.getNextBirthday(&birthday_db, n, "second"));
                  break;
                  case 19: ImGui::Text("WILL BE ON A %s [%d]", DB_clock.getNextWeekDayOfBirthday(&birthday_db, n).c_str(), DB_clock.getNextBirthday(&birthday_db, n, "year"));
                  break;
                  case 21:
                  if(DB_clock.getTotalDaysUntilBirthday(&birthday_db, n) == 0){
                    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,0.75f), "DAYS LEFT 0,    HAPPY BIRTHDAY :D");
                  }else{
                    ImGui::Text("%d DAYS LEFT", DB_clock.getTotalDaysUntilBirthday(&birthday_db, n));
                  }
                  break;
                  case 23:
                  if(DB_clock.getTotalDaysUntilBirthday(&birthday_db, n) == 0){
                    ImGui::TextColored(ImVec4(1.0f,1.0f,0.0f,0.75f), "HOURS LEFT 0,   HAPPY BIRTHDAY :D");
                  }else{
                    ImGui::Text("%d HOURS LEFT", DB_clock.getTotalHoursUntilBirthday(DB_clock.getTotalDaysUntilBirthday(&birthday_db, n)));
                  }
                  break;
                  case 25:
                  if(DB_clock.getTotalDaysUntilBirthday(&birthday_db, n) == 0){
                    ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,0.75f), "MINUTES LEFT 0, HAPPY BIRTHDAY :D");
                  }else{
                    ImGui::Text("%d MINUTES LEFT", DB_clock.getTotalMinutesUntilBirthday(DB_clock.getTotalHoursUntilBirthday(DB_clock.getTotalDaysUntilBirthday(&birthday_db, n))));
                  }
                  break;
                  case 27:
                  if(DB_clock.getTotalDaysUntilBirthday(&birthday_db, n) == 0){
                    ImGui::TextColored(ImVec4(0.0f,0.65f,0.84f,1.0f), "SECONDS LEFT 0, HAPPY BIRTHDAY :D");
                  }else{
                    ImGui::Text("%d SECONDS LEFT", DB_clock.getTotalSecondsUntilBirthday(DB_clock.getTotalMinutesUntilBirthday(DB_clock.getTotalHoursUntilBirthday(DB_clock.getTotalDaysUntilBirthday(&birthday_db, n)))));
                  }
                  break;
                  default: ImGui::Text("soy la respuesta %d", cell);
                  break;
                }

              }
            }
            ImGui::EndTable();
          }
        }
      }
      ImGui::TreePop();
    }
  }else {
    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "THE BIRTHDAY TABLE DOESN'T EXIST, PLEASE CREATE ONE!!");
  }
  style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
}

void Database::NextBirthdaysInThisMonths() {

  const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;
  unsigned int flags = flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;

  ImGui::SetNextItemOpen(false, ImGuiCond_Once);
  char name[50] = "BIRTHDAYS IN THIS MONTH: \0";
  strcat(name, DB_clock.getMonthName());

  ImGuiStyle * style = &ImGui::GetStyle();
  style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 0.0f, 0.0f, 0.75f);
  if(birthday_db.table_names.capacity() > 0 && (int)birthday_db.table_names.size() > 0) {
    if (ImGui::TreeNode(name)) {
      int rows = 0;
      if ((int)birthday_db.column_names[0].size() != 0) {
        rows = ((int)birthday_db.table_data[0].size() / (int)birthday_db.column_names[0].size());
      }
      style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
      static ImGuiTextFilter filter;
      DB_imgui.SetInputColor("blue");
      filter.Draw("WRITE HERE THE USER THAT YOU ARE LOOKING FOR", 200.0f);
      DB_imgui.SetInputColor("gray");
      for(int i = 0; i < rows; i++){
        if(strcmp(birthday_db.table_data[0][3 + (6 * i)].c_str(), DB_clock.getMonthName()) == 0) {
          char buf[100] = "\0";
          strcat(buf, birthday_db.table_data[0][(6 * i)].c_str()); //ID
          strcat(buf, ": ");
          strcat(buf, birthday_db.table_data[0][1 + (6 * i)].c_str()); //Nombre
          if (filter.PassFilter(buf)) {
            bool open = ImGui::CollapsingHeader(buf);
            if (open && ImGui::BeginTable("Table2", 2, flags)) {
              ImGui::TableSetupColumn("QUESTION", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 33.0f);
              ImGui::TableSetupColumn("ANSWER", ImGuiTableColumnFlags_NoHide);
              ImGui::TableHeadersRow();
              for (int cell = 0; cell < 4; cell++) {
                ImGui::TableNextColumn();
                if(cell%2 == 0) {
                  DB_imgui.SetButtonColor("gray");
                  switch(cell) {
                    case 0: ImGui::Button("TOTAL TIME UNTIL NEXT BIRTHDAY:", ImVec2(-FLT_MIN, 0.0f));
                    break;
                    case 2: ImGui::Button("NEXT BIRTHDAY WEEK DAY:", ImVec2(-FLT_MIN, 0.0f));
                    break;
                  }
                  DB_imgui.SetButtonColor("blue");
                }else{
                  switch(cell) {
                    case 1:
                    if(DB_clock.getTotalDaysUntilBirthday(&birthday_db, i) == 0){
                      ImGui::TextColored(ImVec4(0.0f,0.65f,0.84f,1.0f), "DAYS LEFT 0, HAPPY BIRTHDAY :D");
                    }else{
                      ImGui::Text("%d MONTHS,", DB_clock.getNextBirthday(&birthday_db, i, "month")); ImGui::SameLine();
                      ImGui::Text("%d DAYS,", DB_clock.getNextBirthday(&birthday_db, i, "day")); ImGui::SameLine();
                      ImGui::Text("%d HOURS,", DB_clock.getNextBirthday(&birthday_db, i, "hour")); ImGui::SameLine();
                      ImGui::Text("%d MINUTES AND", DB_clock.getNextBirthday(&birthday_db, i, "minute")); ImGui::SameLine();
                      ImGui::Text("%d SECONDS UNTIL BIRTHDAY :D", DB_clock.getNextBirthday(&birthday_db, i, "second"));
                    }
                    break;
                    case 3: ImGui::Text("WILL BE ON A %s [%d]", DB_clock.getNextWeekDayOfBirthday(&birthday_db, i).c_str(), DB_clock.getNextBirthday(&birthday_db, i, "year"));
                    break;
                  }
                }
              }
              ImGui::EndTable();
            }
          }
        }
      }
      ImGui::TreePop();
    }
  }
  style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
}

void Database::BirthdaysToday(Kirby *act_kirby) {
  if(birthday_db.table_names.capacity() > 0 && (int)birthday_db.table_names.size() > 0) {
    int rows = 0;
    if ((int)birthday_db.column_names[0].size() != 0) {
      rows = ((int)birthday_db.table_data[0].size() / (int)birthday_db.column_names[0].size());
    }
    static int coincidences = 0;
    for(int i = 0; i < rows; i++){
      if(strcmp(birthday_db.table_data[0][3 + (6 * i)].c_str(), DB_clock.getMonthName()) == 0) {
        if(strcmp(birthday_db.table_data[0][2 + (6 * i)].c_str(), DB_clock.getDay()) == 0) {
          printf("TODAY'S BIRTHDAY: %s\n", birthday_db.table_data[0][1 + (6 * i)].c_str());
          if(coincidences > 0) {
            strcat(act_kirby->todaysBirthday, ", ");
            strcat(act_kirby->todaysBirthday, birthday_db.table_data[0][1 + (6 * i)].c_str());
          }else{
            strcat(act_kirby->todaysBirthday, birthday_db.table_data[0][1 + (6 * i)].c_str());
          }
          coincidences++;
          act_kirby->activateAnimation();
        }
      }
    }
  }
}

/*
void validate(int value, int lower, int upper, const std::string& desc) {
    if (value < lower || value > upper) {
        throw std::invalid_argument{ "Invalid " + desc + " entered: '" + std::to_string(value) + "'" };
    }
}
*/

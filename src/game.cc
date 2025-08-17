/**
 * @file   game.cc
 * @brief  game file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */
#include <string>
#include "game.h"

Game::Game() {

}

Game::~Game() {

}

void Game::init() {
  TTF_Init();
  my_database.DB_clock.initPointers();
  my_database.initDB();


  window.create("BIRTHDAYS MANAGER (V8.2) BY SEBITAS :D");
  window.setWindowIcon("../data/sprites/icon.png");
  my_clock.setX(window.SCREEN_WIDTH * 0.8f);
  my_clock.setY(window.SCREEN_HEIGHT * 0.35f);
  my_clock.init();
  my_imgui.init(window);


  //Kirby:
  kirby.init(SCREEN_WIDTH_ * 0.75f, SCREEN_HEIGHT_ * 0.9f);
  my_database.BirthdaysToday(&kirby); //para saber si hay cumples hoy
  sprite.createSprite(kirby.vector_KirbyPainting, kirby_paths1, window.renderer_);
  sprite.createSprite(kirby.vector_KirbyWalking, kirby_paths2, window.renderer_);
  sprite.createSprite(kirby.vector_Paint, kirby_paths3, window.renderer_);
  kirby.set_scale(Vector2(1.0f, 1.0f));
}

void Game::update() {
  while (!close) {
    if(SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if(event.type == SDL_QUIT) close = true;
      if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
          event.window.windowID == SDL_GetWindowID(window.window_)) close = true;
        //Close Window with ESC
      if(event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
          case SDLK_ESCAPE: close = true; break;
        }
      }
    }
    window.updateTime();
    my_database.DB_clock.updateTimerClock(); //actualizar las variables de tiempo


    my_imgui.MyStyleSettings(); //ventana toh wapah y con styles depresivos :D

    //CLOCK SETTINGS
    my_imgui.update(window);
    if(kirby.animation == noAnimation && kirby.finish == false) {
      my_imgui.setWindowStatic(350.0f, 200.0f, SCREEN_WIDTH_ * 0.675f, 480.0f);
      my_imgui.newWindow("CLOCK SETTINGS", false, false);
      my_clock.imguiClockWindow();
      my_imgui.end();
    }

    //DATABASE MANAGER
    static ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable;
    my_imgui.setWindow(900.0f, 600.0f, 15.0f, 80.0f);
    my_imgui.newWindow("DATABASES MANAGER", false, false);
    if(ImGui::BeginTabBar("TabBar"), tab_bar_flags) {
      if(ImGui::BeginTabItem("BIRTHDAYS DATABASE")){
        my_database.BirthdayDataBaseImGui();
        ImGui::EndTabItem();
      }
      if(ImGui::BeginTabItem("BIRTHDAYS MANAGER")){
        my_database.BirthdayUsers();
        my_database.NextBirthdaysInThisMonths();
        ImGui::EndTabItem();
      }
      if(ImGui::BeginTabItem("NORMAL TABLES DATABASE")){
        my_database.DataBaseImGui();
        ImGui::EndTabItem();
      }
        if(ImGui::BeginTabItem("CHANGE IMGUI COLOR")){
        my_database.ImGuiColorChanger();
        ImGui::EndTabItem();
      }
      ImGui::EndTabBar();
    }
    my_imgui.end();

    //ImGui::ShowDemoWindow();

    my_clock.updateTimerClock();
    my_clock.clockSound();

    /*Draw background*/
    window.clear(Vector4(0, 0, 0, 255));

    /*Draw Clock and it's things*/
    my_clock.draw(&window);
    my_clock.ShowBirthdaysName(&kirby, &window);

    kirby.update(window.renderer_, window.delta_time_);
    //printf("%d\n", kirby.animation);

    my_imgui.render();
    window.display();
  }
}

void Game::release() {

  kirby.free();
  my_clock.freePointers();
  my_database.DB_clock.freeDatePointers();
  my_database.FreeDB();
  MM->status();
  MM->destroy();
  my_imgui.destroy();
  window.destroy();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

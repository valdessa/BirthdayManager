/**
 * @file   my_imgui.cc
 * @brief  my_imgui file
 *
 * @author Sebastián Valdés (valdessa) "valdessa@esat-alumni.com"
 * @date   December 2021
 */

#include <SDL.h>

#include "window.h"
#include "my_imgui.h"

MyImGui::MyImGui() {

}

void MyImGui::init(RenderWindow window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//Disable ImGui.ini 
	io.IniFilename = nullptr;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(window.window_);
	ImGui_ImplSDLRenderer_Init(window.renderer_);
}

void MyImGui::update(RenderWindow window) {
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame(window.window_);
	ImGui::NewFrame();
}

void MyImGui::setWindow(float size_x, float size_y, float pos_x, float pos_y) {
	static bool done = false;
	if(!done){
		ImGui::SetNextWindowSize(ImVec2(size_x, size_y));
		ImGui::SetNextWindowPos(ImVec2(pos_x, pos_y));
		done = true;
	}
}

void MyImGui::setWindowStatic(float size_x, float size_y, float pos_x, float pos_y) {
	ImGui::SetNextWindowSize(ImVec2(size_x, size_y));
	ImGui::SetNextWindowPos(ImVec2(pos_x, pos_y));
}

void MyImGui::newWindow(const char *name, bool resize, bool move) {
	if(resize && move) {
		ImGui::Begin(name, 0);
	}

	if(!resize && !move) {
		ImGui::Begin(name, 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	}

	if(!resize && move) {
		ImGui::Begin(name, 0, ImGuiWindowFlags_NoResize);
	}

	if(resize && !move) {
		ImGui::Begin(name, 0, ImGuiWindowFlags_NoMove);
	}
}

void MyImGui::MyStyleSettings() {
	ImGuiStyle * style = &ImGui::GetStyle();
     
	//style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	//style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;
	
	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.95f, 0.16f, 0.4f); //mio
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	//style->Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.18f, 0.24f, 1.00f); //tocado por mi
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);


	style->Colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TabActive] = ImVec4(0.26f, 0.65f, 0.67f, 0.50f); //tocado por mi
}

void MyImGui::SetButtonColor(const char *color) {
	ImGuiStyle& style = ImGui::GetStyle();
	switch(MAKECODE(color)) {
		//Red
		case MAKECODE("red"): 
			style.Colors[ImGuiCol_Button] =         ImVec4(0.95f, 0.16f, 0.2f, 0.4f);
  		style.Colors[ImGuiCol_ButtonActive] =   ImVec4(0.95f, 0.32f, 0.2f, 0.8f);
  		style.Colors[ImGuiCol_ButtonHovered] =  ImVec4(0.95f, 0.16f, 0.2f, 1.0f);
		break;
		//Green
		case MAKECODE("green"):
			style.Colors[ImGuiCol_Button] =         ImVec4(0.2f, 0.95f, 0.16f, 0.4f);
  		style.Colors[ImGuiCol_ButtonActive] =   ImVec4(0.2f, 0.95f, 0.32f, 0.6f);
  		style.Colors[ImGuiCol_ButtonHovered] =  ImVec4(0.2f, 0.95f, 0.16f, 0.8f);
		break;
		//Blue
		case MAKECODE("blue"):
			style.Colors[ImGuiCol_Button] =         ImVec4(0.26f, 0.59f, 0.98f, 0.4f);
 		 	style.Colors[ImGuiCol_ButtonActive] =   ImVec4(0.06f, 0.53f, 0.98f, 1.0f);
  		style.Colors[ImGuiCol_ButtonHovered] =  ImVec4(0.26f, 0.59f, 0.98f, 1.0f);
		break;
		//Gray
		case MAKECODE("gray"):
			style.Colors[ImGuiCol_Button] =         ImColor(31, 30, 31, 128);
 		 	style.Colors[ImGuiCol_ButtonActive] =   ImColor(31, 30, 31, 255);
  		style.Colors[ImGuiCol_ButtonHovered] =  ImColor(41, 40, 41, 255);
		break;
	}
}

void MyImGui::SetInputColor(const char *color) {
	ImGuiStyle& style = ImGui::GetStyle();
	switch(MAKECODE(color)) {
		//Red
		case MAKECODE("red"): 
			style.Colors[ImGuiCol_FrameBg] =         ImVec4(0.95f, 0.16f, 0.2f, 0.4f);
  		style.Colors[ImGuiCol_FrameBgActive] =   ImVec4(0.95f, 0.32f, 0.2f, 0.8f);
  		style.Colors[ImGuiCol_FrameBgHovered] =  ImVec4(0.95f, 0.16f, 0.2f, 1.0f);
		break;
		//Green
		case MAKECODE("green"):
			style.Colors[ImGuiCol_FrameBg] =         ImVec4(0.2f, 0.95f, 0.16f, 0.2f);
  		style.Colors[ImGuiCol_FrameBgActive] =   ImVec4(0.2f, 0.95f, 0.32f, 0.4f);
  		style.Colors[ImGuiCol_FrameBgHovered] =  ImVec4(0.2f, 0.95f, 0.16f, 0.6f);
		break;
		//Blue
		case MAKECODE("blue"):
			style.Colors[ImGuiCol_FrameBg] =         ImVec4(0.26f, 0.59f, 0.98f, 0.2f);
 		 	style.Colors[ImGuiCol_FrameBgActive] =   ImVec4(0.06f, 0.53f, 0.98f, 0.6f);
  		style.Colors[ImGuiCol_FrameBgHovered] =  ImVec4(0.26f, 0.59f, 0.98f, 0.8f);
		break;
		//Gray
		case MAKECODE("gray"):
			style.Colors[ImGuiCol_FrameBg] =         ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
 		 	style.Colors[ImGuiCol_FrameBgActive] =   ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
  		style.Colors[ImGuiCol_FrameBgHovered] =  ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		break;
	}
}

void MyImGui::SetHeaderColor(const char *color) {
	ImGuiStyle& style = ImGui::GetStyle();
	switch(MAKECODE(color)) {
		//Red
		case MAKECODE("red"): 
			style.Colors[ImGuiCol_Header] =         ImVec4(0.95f, 0.16f, 0.2f, 0.4f);
  		style.Colors[ImGuiCol_HeaderActive] =   ImVec4(0.95f, 0.32f, 0.2f, 0.8f);
  		style.Colors[ImGuiCol_HeaderHovered] =  ImVec4(0.95f, 0.16f, 0.2f, 1.0f);
		break;
		//Green
		case MAKECODE("green"):
			style.Colors[ImGuiCol_Header] =         ImVec4(0.2f, 0.95f, 0.16f, 0.4f);
  		style.Colors[ImGuiCol_HeaderActive] =   ImVec4(0.2f, 0.95f, 0.32f, 0.6f);
  		style.Colors[ImGuiCol_HeaderHovered] =  ImVec4(0.2f, 0.95f, 0.16f, 0.8f);
		break;
		//Blue
		case MAKECODE("blue"):
			style.Colors[ImGuiCol_Header] =         ImVec4(0.26f, 0.59f, 0.98f, 0.4f);
 		 	style.Colors[ImGuiCol_HeaderActive] =   ImVec4(0.06f, 0.53f, 0.98f, 1.0f);
  		style.Colors[ImGuiCol_HeaderHovered] =  ImVec4(0.26f, 0.59f, 0.98f, 1.0f);
		break;
		//Gray
		case MAKECODE("gray"):
			style.Colors[ImGuiCol_Header] =         ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
 		 	style.Colors[ImGuiCol_HeaderActive] =   ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
  		style.Colors[ImGuiCol_HeaderHovered] =  ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		break;
	}
}

void MyImGui::addSeparator(int cicles) {
	for(int i = 0; i < cicles; i++) {
		ImGui::Separator();
	}
}

void MyImGui::addSpace(int cicles) {
	for(int i = 0; i < cicles; i++) {
		ImGui::Spacing();
	}
}

void MyImGui::setPositionX(float pos) {
	ImVec2 w_pos = ImGui::GetCursorPos();
	ImGui::SetCursorPos(ImVec2(pos, w_pos.y));
}

void MyImGui::end() {
	ImGui::End();
}

void MyImGui::render() {
	ImGui::Render();
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void MyImGui::destroy() {
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

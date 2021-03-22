#pragma once

#include <SDL2/SDL.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

#include <iostream>

// #include "../include/Scene.hpp"
// #include "../include/Cursor.hpp"
// #include "../include/Lights.hpp"

class Interface {

	private:
		ImVec4 i_color;

	public:
		Interface(SDL_Window* window, SDL_GLContext* glContext);
		~Interface();
		void beginFrame(SDL_Window* window) const;
		void endFrame(SDL_Window* window) const;
		void drawInterface(SDL_Window* window);
		bool isMouseOnInterface() const;

};
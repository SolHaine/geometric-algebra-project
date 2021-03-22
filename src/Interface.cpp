#include "../include/Interface.hpp"

Interface::Interface(SDL_Window* window, SDL_GLContext* glContext) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, &glContext);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

Interface::~Interface() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Interface::beginFrame(SDL_Window* window) const {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();
}

void Interface::endFrame(SDL_Window* window) const {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Interface::drawInterface(SDL_Window* window) {
    
    ImGuiIO &i_io = ImGui::GetIO();
    ImGuiStyle &i_style = ImGui::GetStyle();
    i_style.WindowRounding = 0.2f;

    // render your GUI
    ImGui::Begin("Demo window");
    ImGui::Button("Hello!");
    ImGui::End();

    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    int display_w, display_h;    
    
}

bool Interface::isMouseOnInterface() const {
    ImGuiIO &i_io = ImGui::GetIO();
    return i_io.WantCaptureMouse;
}


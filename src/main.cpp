#include <GL/glew.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

#include <iostream>
#include <numeric>

#include "../include/View.hpp"
#include "../include/FreeFlyCamera.hpp"
#include "../include/Interface.hpp"


#include <c3ga/Mvec.hpp>
#include "c3gaTools.hpp"

/*
join point(p1,p2)
    l1 = dual(1)
    l2 = dual(p2)
    intersect_point = intersect_lines(l1, l2);
    return dual(intersec_point)
*/
using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(1024, 768, "Geometric Algebra Project");
    SDL_GL_SetSwapInterval(1);

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    // Display versions
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    // Definition of projection matrix
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);

    /*********************************
    * INITIALIZATION CODE
    *********************************/
    
    // Definition of view (load, compile and use shaders)
    FilePath applicationPath(argv[0]);
    View view(applicationPath);

    // Definition of camera
    FreeFlyCamera Camera;

    // Definition of interface
    Interface interface(windowManager.window, &windowManager.openglContext);

    /*********************************
    * APPLICATION LOOP
    *********************************/

    static bool done = false;
    static const Uint32 FRAMERATE_MILLISECONDS = 1000/60;

    while(!done) {
        // Time
        Uint32 startTime = SDL_GetTicks();

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            ImGui_ImplSDL2_ProcessEvent(&e);

            // Leave the loop after this iteration
            if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                done = true;
            }
        }

        /*********************************
         * RENDERING CODE
         *********************************/
       
        // Clean window and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate depth
        glEnable(GL_DEPTH_TEST);
        
        // Choose program
        view.useView();

        // Definition of matrix
        glm::mat4 MMatrix;
        glm::mat4 ViewMatrix = Camera.getViewMatrix();
        glm::mat4 MVMatrix = ViewMatrix * MMatrix;
        // Send uniforms (view matrix and textures)
        view.sendMatrixView(MVMatrix, ProjMatrix);

        /* --------- Interface --------- */
        // Draw interface
        interface.beginFrame(windowManager.window);
        interface.drawInterface(windowManager.window);
        interface.endFrame(windowManager.window);

        /* --------- Implement Sphere --------- */

        // Update the display
        windowManager.swapBuffers();

        // Time
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS){
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    return 0;
}
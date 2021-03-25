#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include "glimac/glm.hpp"
#include <cstddef>
#include <c2ga/Mvec.hpp>
#include "../include/c2gaTools.hpp"
#include "../include/drawing.hpp"

using namespace std;
using namespace glimac;

class Vertex2DColor
{

public:
    glm::vec2 position;
    glm::vec3 color;

    Vertex2DColor() {}
    Vertex2DColor(glm::vec2 p_position, glm::vec3 p_color) : position(p_position),
                                                             color(p_color)
    {
    }
};

//Main function 
//Draw windows
//Generates shapes and textures
int main(int argc, char **argv)
{
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError)
    {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "../shaders/color.vs.glsl",
                                  applicationPath.dirPath() + "../shaders/color.fs.glsl");
    program.use();

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    //Test
    //create c2ga point
    Mvec<double> p = point(0.0,0.0);

    Mvec<double> line = !p;

    // vbo creation
    GLuint vbo;
    glGenBuffers(1, &vbo);

    //Bindind vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //Coordonates
    Vertex2DColor vertices[] = {
        Vertex2DColor(glm::vec2(-0.5, -0.5), glm::vec3(1, 0, 0)),
        Vertex2DColor(glm::vec2(0.5, -0.5), glm::vec3(0, 1, 0)),
        Vertex2DColor(glm::vec2(0, 0.5), glm::vec3(0, 0, 1))};

    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex2DColor), vertices, GL_STATIC_DRAW);

    //Débinder
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vao Creation
    GLuint vao;
    glGenVertexArrays(1, &vao);

    //Bindind vao
    //glBindersVertexArray(GL_ARRAY_BUFFER);
    glBindVertexArray(vao);

    //Attributs activation
    //au lieu de faire ça glEnableVertexAttribArray(0);
    //To what corresponds the 0
    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    const GLuint VERTEX_ATTR_COLOR = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    //rebinder le VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid *)offsetof(Vertex2DColor, position));
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid *)offsetof(Vertex2DColor, color));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //débinder VAO
    glBindVertexArray(0);

    // Application loop:
    bool done = false;
    while (!done)
    {
        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e))
        {
            if (e.type == SDL_QUIT)
            {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        //Nettoyer la fenêtre
        glClear(GL_COLOR_BUFFER_BIT);

        //rebinder vao
        glBindVertexArray(vao);

        //dessiner sommet
        //drawPoint(p);
        drawCircle(p, 1.0);
        drawLine(line);
        //unsigned int indexes[]= {0,1};
        
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_LINES, 0, 2);

        //débinder
        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}

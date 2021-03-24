#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include "glimac/glm.hpp"
#include "glimac/Sphere.hpp"
#include "glimac/common.hpp"

using namespace glimac;
using namespace glm;
using namespace std;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    //Loading shaders
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/" + argv[1],
                                    applicationPath.dirPath() + "shaders/" + argv[2]);
    program.use();

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    //definition locations variables uniformes
    GLint uLocationMVP = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uLocationMV = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uLocationNormal = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    // GPU checks depth
    glEnable(GL_DEPTH_TEST);

    mat4 ProjMatrix = perspective(radians(70.f),800.f/600.f,0.1f, 100.f);

    mat4 MVMatrix = translate(mat4(),vec3(0.f,0.f,-5.f));

    mat4 NormalMatrix = transpose(inverse(MVMatrix));


    

    //Initialisation sphere
    Sphere sphere(1, 16, 16);





    //vbo creation
    GLuint vbo;
    glGenBuffers(1, &vbo);

    //Binding vbo
    glBindBuffer(GL_ARRAY_BUFFER,vbo);

    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount() * sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);

    //débinder
    glBindBuffer(GL_ARRAY_BUFFER,0);

    //vao creation
    GLuint vao;
    glGenVertexArrays(1,&vao);

    //Binding vao
    glBindVertexArray(vao);

    //attributs activation
    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    const GLuint VERTEX_ATTR_NORMAL = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);

    const GLuint VERTEX_ATTR_TEXTURE = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

    //rebinder le VBO
    glBindBuffer(GL_ARRAY_BUFFER,vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));

    glBindBuffer(GL_ARRAY_BUFFER,0);

    //debinder VAO
    glBindVertexArray(0);




    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        //Clear the window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUniformMatrix4fv(uLocationMVP, 1, GL_FALSE , value_ptr(ProjMatrix*MVMatrix));
        glUniformMatrix4fv(uLocationMV, 1,  GL_FALSE, value_ptr(MVMatrix));
        glUniformMatrix4fv(uLocationNormal, 1,  GL_FALSE, value_ptr(NormalMatrix));

        //rebinder vao
        glBindVertexArray(vao);

        //cout << "je suis là" << endl;
        

        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
        
        // for (GLsizei i=0; i<sphere.getVertexCount(); i++) {
        //     glDrawArrays(GL_TRIANGLES, i, 3);
        // }

        glBindVertexArray(0);


        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1,&vao);

    return EXIT_SUCCESS;
}
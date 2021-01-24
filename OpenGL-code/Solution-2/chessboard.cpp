

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "utility/shader.hpp"
#include "utility/readfile.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void chessmatrix();
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

float step = 0.2f;
const int arr_size = 8*8*2*3*6;
GLfloat *vertices;
int main()
{   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Soviet Republic", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    chessmatrix();
    glViewport(0, 0,SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader *shdr = new Shader("shaders/shad1.vs","shaders/shad1.fs");    
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers( 1, &VBO );
    
    
    glBindVertexArray( VAO );

    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, arr_size* sizeof( GLfloat ), vertices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 3* sizeof( GLfloat ), (GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 1, 1, GL_FLOAT, GL_FALSE, 3* sizeof( GLfloat ), (GLvoid * ) (2* sizeof(GLfloat)) );
    glEnableVertexAttribArray( 1 );

    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window);

        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shdr->use();

        glBindVertexArray( VAO );

        glDrawArrays(GL_TRIANGLES, 0, arr_size/6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
int ind=0;
void chessmatrix()
{
    GLfloat startx = -0.8f;
    GLfloat color = 0.0f;
    GLfloat incr =0.2f;
    vertices = new GLfloat[arr_size];
    for (int i=0; i<8; i++)
    {
        
        GLfloat starty = -0.8f;
        for (int j=0; j<8; j++)
        {
            vertices[ind+0] = startx;
            vertices[ind+1] = starty;
            vertices[ind+2] =  color;

            vertices[ind+3] = startx;
            vertices[ind+4] = starty+incr;
            vertices[ind+5] =  color;


            vertices[ind+6] = startx+incr;
            vertices[ind+7] = starty;
            vertices[ind+8] =  color;

            vertices[ind+9] =  startx;
            vertices[ind+10] = starty+incr;
            vertices[ind+11] =  color;

            vertices[ind+12] = startx+incr;
            vertices[ind+13] = starty;
            vertices[ind+14] =  color;


            vertices[ind+15] = startx+incr;
            vertices[ind+16] = starty+incr;
            vertices[ind+17] =  color;
            
            ind+=18;
            starty+=0.2f;
            if(color == 0.0f)
            color = 1.0f;
            else if(color == 1.0f)
            color = 0.0f;
        }
        if(color == 0.0f)
            color = 1.0f;
        else if(color == 1.0f)
            color = 0.0f;
        startx+=0.2f;
    }

}
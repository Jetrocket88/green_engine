#include <iostream>
//#include <assert.h>
#include <cmath>
#include <sstream>
#include <fstream>
#include <windows.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../vendor/glm/glm.hpp"

#include "core/window.h"
#include "core/error.h"
#include "renderer/shader.h"
#include "renderer/vbo.h"
#include "renderer/vao.h"
#include "renderer/ibo.h"

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } 
}

int main() {

    glfw_setup();

    Window window(800, 600, "Hello world!");

    window.window_init();
    glad_setup();
    window.veiwport();
    window.callbacks_setup();

    Shader shader;
    shader.load_shaders("assets/shaders/vertex.shader", "assets/shaders/fragment.shader");
    shader.bind();

    const float vertices[] = {
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };

    const unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
    };  

    VBO vbo;
    vbo.add_data(vertices, sizeof(vertices) / sizeof(vertices[0]));

    VAO vao;
    vao.bind();

    IBO ibo;
    ibo.add_data(indices, sizeof(indices) / sizeof(indices[0]));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glCheckError();

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glCheckError();

    vao.unbind();

    while(!glfwWindowShouldClose(window.ptr))
    {
        processInput(window.ptr);
        
        //opengl stuff goes here
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        glm::vec4 vec = {0.2f, greenValue, 0.2f, 1.0f};
        //shader.set_vec4f("ourColor", vec);
        glCheckError();

        shader.bind();
        vao.bind();
        ibo.bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window.ptr);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}


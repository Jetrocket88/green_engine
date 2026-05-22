#include <iostream>
#include <cmath>
#include <sstream>
#include <fstream>
#include <windows.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"

#include "core/window.h"
#include "core/error.h"
#include "renderer/shader.h"
#include "renderer/vbo.h"
#include "renderer/vao.h"
#include "renderer/ibo.h"
#include "renderer/texture.h"
#include "renderer/text.h"
#include "renderer/renderer.h"
#include "renderer/camera.h"

#include "core/state.h"


int main() {

    ApplicationSate state{};

    Window window(800, 600, "Green_Engine");
    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(window.ptr, &state);
    
    Shader shader;
    shader.load_shaders("assets/shaders/vertex.shader", "assets/shaders/fragment.shader");
    shader.bind();

    Texture texture("assets/images/image.jpg", 0);
    
    Vertex v[4];
    v[0].position = glm::vec3(1.0f, 1.0f, 0.0f      );
    v[0].color =    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    v[0].texCoord = glm::vec2(1.0f, 1.0f            );

    v[1].position = glm::vec3(1.0f, -1.0f, 0.0f     );
    v[1].color =    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    v[1].texCoord = glm::vec2(1.0f, 0.0f            );

    v[2].position = glm::vec3(-1.0f, -1.0f, 0.0f    );
    v[2].color =    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    v[2].texCoord = glm::vec2(0.0f, 0.0f            );

    v[3].position = glm::vec3(-1.0f, 1.0f, 0.0f     );
    v[3].color =    glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    v[3].texCoord = glm::vec2(0.0f, 1.0f            );
    
    const unsigned int indices[] = { 
        0, 1, 3,   
        1, 2, 3
    };  

    VAO vao;
    vao.bind();

    VBO vbo;
    vbo.add_data(v, sizeof(v));

    IBO ibo;
    ibo.add_data(indices, sizeof(indices) / sizeof(indices[0]));

    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glCheckError();

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    glCheckError();

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, texCoord)));
    glEnableVertexAttribArray(2);
    glCheckError();

    vao.unbind();
    glfwSetInputMode(window.ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window.ptr, [](GLFWwindow*w, double x, double y) {
        auto* s = static_cast<ApplicationSate*>(glfwGetWindowUserPointer(w));
        if (!s) return;
        s->camera.on_mouse_move(x, y);
    });

    Camera       &cam = state.camera;
    InputState &input = state.input;

    while(!glfwWindowShouldClose(window.ptr))
    {
        //Calculate delta_time ---------------------------------------------------------------
        float current_frame = glfwGetTime();
        state.delta_time = current_frame - state.last_frame;
        state.last_frame = current_frame;

        //Camera and matrix stuff ------------------------------------------------------------
        glm::mat4 model = glm::mat4(1.0f);

        cam.update_pos(&input.keys[0], state.delta_time);
        glm::mat4 view = cam.calculate_view();

        glm::mat4 projection = glm::mat4(1.0f);
        const float fov = 45.0f;
        projection = glm::perspective(glm::radians(fov), (float)window.width / (float)window.height, 0.1f, 100.0f);
        
        //opengl stuff goes here ------------------------------------------------------------- 
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glCheckError();

        shader.bind();
        shader.set_mat4f("view"      , &view      );
        shader.set_mat4f("projection", &projection);
        shader.set_mat4f("model",      &model     );

        texture.bind();
        vao.bind();
        ibo.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glCheckError();
        //-------------------------------------------------------------------------------------

        //Populates the state.input.keys array with the values of the pressed keys 
        poll_input(window.ptr, state.input);

        glfwSwapBuffers(window.ptr);
        glfwPollEvents();    

        check_exit(window.ptr, &input.keys[0]);
    }

    glfwTerminate();
    return 0;
}


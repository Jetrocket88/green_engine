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

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/backends/imgui_impl_glfw.h"
#include "../vendor/imgui/backends/imgui_impl_opengl3.h"

#include "core/window.h"
#include "core/error.h"
#include "core/state.h"
#include "core/input_state.h"

#include "renderer/shader.h"
#include "renderer/vbo.h"
#include "renderer/vao.h"
#include "renderer/ibo.h"
#include "renderer/texture.h"
#include "renderer/text.h"
#include "renderer/renderer.h"
#include "renderer/camera.h"
#include "renderer/renderer.h"
#include "renderer/model_loader.h"

glm::vec4 RED = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
glm::vec4 GRAY = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);

int main() {

    ApplicationSate state{};

    Window window(800, 600, "Green_Engine");
    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(window.ptr, &state);
    
    Renderer renderer; 
    renderer.init(window.ptr);

    glfwSetCursorPosCallback(window.ptr, [](GLFWwindow*w, double x, double y) {
        auto* s = static_cast<ApplicationSate*>(glfwGetWindowUserPointer(w));
        if (!s) return;
        if (s->paused) return;
        s->camera.on_mouse_move(x, y);
    });

    Camera       &cam = state.camera;
    InputState &input = state.input;

    std::vector<glm::vec3> out_vertices, out_normals;
    std::vector<glm::vec2> out_uvs;

    ModelLoader::load_obj(
        "assets/models/test.obj",
        out_vertices,
        out_uvs,
        out_normals
    );



    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(window.ptr, true);
    ImGui_ImplOpenGL3_Init("#version 330");
     
    ImGui::StyleColorsDark(); 
    glm::mat4 view = glm::mat4(1.0f);
    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    while(!glfwWindowShouldClose(window.ptr))
    {
        // Start of frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Your ImGui calls go here
        std::string movement = "Walking";
        if (cam.cam_speed > 0.007f) movement = "Sprinting";
        else movement = "Walking";

        ImGui::Begin("Debug");
        ImGui::Text(movement.c_str());
        ImGui::SliderFloat("Camera Near Plane", &nearPlane, 0.01f, 10.0f);
        ImGui::SliderFloat("Camera Far Plane", &farPlane, 50.0f, 150.0f);
        ImGui::SliderFloat("FOV Slider", &fov, 30.0f, 100.0f);
        ImGui::End();

        state.calculate_dt();

        //Camera and matrix stuff ------------------------------------------------------------
        glm::mat4 model = glm::mat4(1.0f);

        view = cam.calculate_view();
        if (!state.paused)
            cam.update_pos(&input.keys[0], &input.prev_keys[0], state.delta_time); 

        glm::mat4 projection = glm::perspective(
            glm::radians(fov),
            (float)window.width / (float)window.height,
            nearPlane,
            farPlane
        );
        
        //Managing Pausing the game
        //Might not be a part of the actual game
        if (state.input.just_pressed(GLFW_KEY_F)) {
            state.paused = !state.paused; 
            if (state.paused)  {
                glfwSetInputMode(window.ptr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                cam.first_mouse = true;
            }
            else {
                glfwSetInputMode(window.ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        }

        if (!state.paused) { renderer.render_solid_background(GRAY); }
        else               { renderer.render_solid_background(RED ); }

        MVP mvp = (MVP){ .model = model, .view = view, .projection = projection };
        renderer.begin_frame(mvp);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        input.poll_input(window.ptr);
        renderer.end_frame(window.ptr);

        check_exit(window.ptr, &input.keys[0]);
    }

    glfwTerminate();
    return 0;
}


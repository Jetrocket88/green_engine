#ifndef STATE_H
#define STATE_H

#include "renderer/camera.h"


struct InputState {
    bool keys[GLFW_KEY_LAST] = {};
    float mouse_x, mouse_y;
    float scroll_delta;
};

struct ApplicationSate {
    Camera    camera;
    InputState input;
    float delta_time = 0.0f;
    float last_frame = 0.0f;
};


void poll_input(GLFWwindow* window, InputState& input) {
    for (int key = 0; key < GLFW_KEY_LAST; key++) {
        input.keys[key] = glfwGetKey(window, key) == GLFW_PRESS;
    }
}

#endif //STATE_H

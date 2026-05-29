#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstring>

class InputState {
private:
    bool keys      [GLFW_KEY_LAST] = {};
    bool prev_keys [GLFW_KEY_LAST] = {};
    float mouse_x, mouse_y;
    float scroll_delta;

public:
    InputState();
    void init(); 

    void poll_input(GLFWwindow* window) {
        memcpy(prev_keys, keys, sizeof(keys));
        for (int key = 0; key < GLFW_KEY_LAST; key++) {
            keys[key] = glfwGetKey(window, key) == GLFW_PRESS;
        }
    }
    bool just_pressed(int key) const {
        return keys[key] && !prev_keys[key];
    }
    static bool just_pressed_static(bool* keys, bool* prev_keys, int key) {
        return keys[key] && !prev_keys[key];
    }
};

#endif //INPUT_STATE_H

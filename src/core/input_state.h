#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstring>

class InputState {
private:
    bool  m_keys      [GLFW_KEY_LAST] = {};
    bool  m_prev_keys [GLFW_KEY_LAST] = {};
    float m_mouse_x, m_mouse_y;
    float m_scroll_delta;

public:
    InputState();
    void init(); 

    void poll_input(GLFWwindow* window);
    bool just_pressed(int key) const;
    bool pressed     (int key) const { return m_keys[key]; }
};

#endif //INPUT_STATE_H

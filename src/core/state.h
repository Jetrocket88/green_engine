#ifndef STATE_H
#define STATE_H

#include "renderer/camera.h"
#include "input_state.h"

struct ApplicationSate {
    Camera    camera;
    InputState input;
    float delta_time = 0.0f;
    float last_frame = 0.0f;
    bool paused = false;

    void calculate_dt() {
        float current_frame = glfwGetTime();
        this->delta_time = current_frame - this->last_frame;
        this->last_frame = current_frame;
    }

};

struct MVP {
    glm::mat4 model, view, projection;
};




#endif //STATE_H

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"

#include <iostream>


class Camera {
public:
    Camera();

    glm::mat4 calculate_view();
    void update_pos(bool* keys, float delta_time);
    void on_mouse_move(double x, double y);
    glm::mat4 get_view();

    float cam_speed          = 0.05f;
    float cam_vertical_speed = 0.025f;
    glm::vec3 camera_pos;

private:
    glm::vec3 camera_front, camera_up,  
    up, camera_target, camera_dir,
    camera_right;
    glm::mat4 view;
    bool first_mouse;
    float lastX, lastY, pitch, yaw;
    
};

#endif //CAMERA_H

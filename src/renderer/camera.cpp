#include "camera.h"

Camera::Camera() = default;

void Camera::init() {
    camera_pos    = glm::vec3(0.0f, 0.0f,  3.0f);
    camera_front  = glm::vec3(0.0f, 0.0f, -1.0f);
    camera_up     = glm::vec3(0.0f, 1.0f,  0.0f);
    camera_target = glm::vec3(0.0f);
    yaw           = -90.0f;
    pitch         =   0.0f;
    cam_speed     =   0.007f;
    first_mouse   =   true;
    lastX = lastY =   0.0f;
}

glm::mat4 Camera::calculate_view() {
    this->view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
    return this->view;
}

void Camera::update_pos(bool *keys, bool *prev_keys, float delta_time) {
    this->camera_dir   = glm::normalize(this->camera_pos - this->camera_target);
    this->camera_right = glm::normalize(glm::cross(this->camera_up, this->camera_dir));

    if (keys[GLFW_KEY_W]) { 
        this->camera_pos.x += cam_speed * this->camera_front.x;
        this->camera_pos.z += cam_speed * this->camera_front.z;
    }
    if (keys[GLFW_KEY_S]) {
        this->camera_pos.x -= cam_speed * this->camera_front.x;
        this->camera_pos.z -= cam_speed * this->camera_front.z;
    }

    if (keys[GLFW_KEY_D]) { this->camera_pos += cam_speed * this->camera_right; }
    if (keys[GLFW_KEY_A]) { this->camera_pos -= cam_speed * this->camera_right; }

    if (keys[GLFW_KEY_LEFT_SHIFT]) { this->camera_pos -= cam_speed * camera_up; }
    if (keys[GLFW_KEY_SPACE])      { this->camera_pos += cam_speed * camera_up; }

    if (InputState::just_pressed_static(keys, prev_keys, GLFW_KEY_LEFT_CONTROL)) {
        if (this->cam_speed == 0.007f) {
            this->cam_speed *= 2.3;
        } else {
            this->cam_speed = 0.007f;
        }
    }
}

void Camera::on_mouse_move(double x, double y) {
    
    if (this->first_mouse) {
        lastX = x;
        lastY = y;
        first_mouse = false;
    }

    float xoffset = x - lastX;
    float yoffset = lastY - y;
    lastX = x;
    lastY = y;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if (pitch >= 89.0f) pitch = 89.0f;
    if (pitch <= -89.0f) pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->camera_front = glm::normalize(direction); 
}

glm::mat4 Camera::get_view() {
    return this->view;
}

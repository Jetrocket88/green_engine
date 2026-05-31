#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"

#include "../core/input_state.h"
#include "../core/services.h"

#include "renderer.h"
#include <iostream>

class Camera {
public:
    Camera();
    void init();

    void update(float dt);
    void on_mouse_move(double x, double y);

    glm::mat4 get_view_matrix()       const {return m_view;      }
    glm::mat4 get_projection_matrix() const {return m_projection;}

    float m_cam_speed          = 0.05f;
    float m_cam_vertical_speed = 0.025f;
    float fov                = 45.0f;
    glm::vec3 m_camera_pos;
    bool first_mouse;

private:
    glm::vec3 m_camera_front, m_camera_up,  
    m_up, m_camera_target, m_camera_dir,
    m_camera_right;

    glm::mat4 m_view       = glm::mat4(1.0f);
    glm::mat4 m_projection = glm::mat4(1.0f);

    float m_lastX, m_lastY, m_pitch, m_yaw;
    
    void calculate_view();
};

#endif //CAMERA_H

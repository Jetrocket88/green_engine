#include "camera.h"

Camera::Camera() = default;

void Camera::init() {
    m_camera_pos    = glm::vec3(0.0f, 0.0f, 3.0f);
    m_camera_front  = glm::vec3(0.0f, 0.0f,-1.0f);
    m_camera_up     = glm::vec3(0.0f, 1.0f, 0.0f);
    m_yaw           = -90.0f;
    m_pitch         =   0.0f;
    m_cam_speed     =   1.127f;
    first_mouse   =   true;
    m_lastX = m_lastY =   0.0f;

    //auto* renderer = Services::get<Renderer>();
    //float width = static_cast<float>(renderer->get_window_width());
    //float height = static_cast<float>(renderer->get_window_height());
    float width = 1280;
    float height = 720;
    m_projection = glm::perspective(
    glm::radians(45.0f),        // FOV
    width / height,           // aspect ratio (width / height)
    0.1f,                       // near clip
    100.0f                      // far clip
);
}

void Camera::update(float dt) {
    auto* input_state = Services::get<InputState>();

    m_camera_right = glm::normalize(glm::cross(m_camera_front, m_camera_up));

    if (input_state->pressed(GLFW_KEY_W)) { 
        m_camera_pos.x += m_cam_speed * m_camera_front.x * dt;
        m_camera_pos.z += m_cam_speed * m_camera_front.z * dt;
    }
    if (input_state->pressed(GLFW_KEY_S)) {
        m_camera_pos.x -= m_cam_speed * m_camera_front.x * dt;
        m_camera_pos.z -= m_cam_speed * m_camera_front.z * dt;
    }

    if (input_state->pressed(GLFW_KEY_D)) { m_camera_pos += m_cam_speed * m_camera_right * dt; }
    if (input_state->pressed(GLFW_KEY_A)) { m_camera_pos -= m_cam_speed * m_camera_right * dt; }

    if (input_state->pressed(GLFW_KEY_LEFT_SHIFT)) { m_camera_pos -= m_cam_speed * m_camera_up * dt; }
    if (input_state->pressed(GLFW_KEY_SPACE))      { m_camera_pos += m_cam_speed * m_camera_up * dt; }

    m_view = glm::lookAt(m_camera_pos, m_camera_pos + m_camera_front, m_camera_up);
}

void Camera::on_mouse_move(double x, double y) {
    
    if (first_mouse) {
        m_lastX = x;
        m_lastY = y;
        first_mouse = false;
    }

    float xoffset = x - m_lastX;
    float yoffset = m_lastY - y;
    m_lastX = x;
    m_lastY = y;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    m_yaw   += xoffset;
    m_pitch += yoffset;

    if (m_pitch >= 89.0f)  m_pitch = 89.0f;
    if (m_pitch <= -89.0f) m_pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_camera_front = glm::normalize(direction); 
}

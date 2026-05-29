#include "renderer.h"

void Renderer::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(1280, 720, "My Engine", nullptr, nullptr);
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }  

    if (!m_window) {
        std::cout << "Failed to create GLFW window!\n";
        glfwTerminate();
        return;
    }
}

void Renderer::shutdown() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

Renderer::Renderer() = default;



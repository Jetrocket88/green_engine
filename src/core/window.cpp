#include "window.h"


const void glfw_setup() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

const int glad_setup() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }  
    return 1;
}



void Window::window_init() {
    GLFWwindow* window = glfwCreateWindow(width, height, text.c_str(), NULL, NULL);
    this->ptr = window;
    if (this->ptr == NULL) {
        std::cout << "Failed to create window! :(";
        glfwTerminate();
    }
    glfwMakeContextCurrent(this->ptr);
}

const void Window::veiwport() {
    glViewport(0, 0, this->width, this->height);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{ glViewport(0, 0, width, height); }

const void Window::callbacks_setup() {
    glfwSetFramebufferSizeCallback(this->ptr, framebuffer_size_callback);
}

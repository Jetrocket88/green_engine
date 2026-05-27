#include "window.h"
#include "GLFW/glfw3.h"

void check_exit(GLFWwindow* window, bool *keys) {
    if (keys[GLFW_KEY_ESCAPE]) { glfwSetWindowShouldClose(window, true); } 
}

Window::Window(size_t width, size_t height, std::string text) {
    this->width = width;
    this->height= height;
    this->text  = text;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, text.c_str(), NULL, NULL);
    this->ptr = window;
    if (this->ptr == NULL) {
        std::cout << "Failed to create window! :(";
        glfwTerminate();
    }

    glfwMakeContextCurrent(this->ptr);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }  

    glViewport(0, 0, this->width, this->height);
    glfwSetInputMode(this->ptr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetInputMode(this->ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(this->ptr, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

}



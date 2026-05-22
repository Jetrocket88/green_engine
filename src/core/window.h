#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void check_exit(GLFWwindow* window, bool *keys);

class Window {
public:

    Window(size_t width, size_t height, std::string text);
    size_t width, height;
    std::string text;
    GLFWwindow* ptr;
};

#endif // WINDOW_H

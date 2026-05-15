#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Window {
public:
    size_t width, height;
    std::string text;
    GLFWwindow* ptr;
    Window(size_t width, size_t height, std::string text) 
        : width(width), height(height), text(text)
    { }
    void window_init();
    const void veiwport();
    const void callbacks_setup();
};

const int glad_setup();
const void glfw_setup();


#endif // WINDOW_H

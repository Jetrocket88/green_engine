#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer/shader.h"


class Renderer {
public:

    void init(GLFWwindow* window);
    void begin_frame();
    //void submit(const Model& model, const Transform& transform);
    void end_frame();
    void shutdown();

private:
    //Camera m_Camera;
    Shader m_Shader;
    //Framebuffer m_Framebuffer;
};


#endif //RENDERER_H


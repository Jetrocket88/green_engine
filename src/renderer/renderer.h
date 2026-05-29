#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

#include <vector>
#include <memory>

#include "core/window.h"
#include "core/state.h"

#include "renderer/shader.h"
#include "renderer/vbo.h"
#include "renderer/vao.h"
#include "renderer/ibo.h"
#include "renderer/texture.h"
#include "renderer/text.h"
#include "renderer/camera.h"
#include "renderer/model.h"


class Renderer {
public:
    Renderer();
    void init();
    void shutdown();

    GLFWwindow* get_window() const { return m_window; };
    bool should_close() const { return glfwWindowShouldClose(m_window); };


private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::unique_ptr<Texture>> textures;

    VAO vao;
    VBO vbo;
    IBO ibo;

    GLFWwindow* m_window = nullptr;
};


#endif //RENDERER_H


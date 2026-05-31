#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

#include <memory>

#include "renderer/shader.h"
#include "renderer/vbo.h"
#include "renderer/vao.h"
#include "renderer/ibo.h"
#include "renderer/texture.h"
#include "renderer/camera.h"
#include "core/services.h"
#include "core/error.h"

#include "renderer/model.h"

struct DrawCall {
    const Model*    model;
    std::string     shader;
    std::string     texture;
    glm::mat4       transform;
};

class Renderer {
public:
    Renderer();
    void init();
    void shutdown();


    GLFWwindow* get_window() const { return m_window; };
    bool should_close() const { return glfwWindowShouldClose(m_window); };
    void update(float dt);
    void submit(const Model* model, std::string shader, std::string texture, const glm::mat4& transform);

    Shader *get_shader(const std::string& name);
    void load_shader(const std::string& name, const std::string& vPath, const std::string& fPath);

    int get_window_width()  const { return m_window_width;  }
    int get_window_height() const { return m_window_height; }

    void set_window_width(int x)  { m_window_width  = x; }
    void set_window_height(int x) { m_window_height = x; }

private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders;
    Shader *active_shader = nullptr;


    std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;

    std::vector<DrawCall> m_draw_queue;

    VAO m_vao;
    VBO m_vbo;
    IBO m_ibo;
    
    GLFWwindow* m_window = nullptr;
    int m_window_width = 1280;
    int m_window_height= 720;
};


#endif //RENDERER_H


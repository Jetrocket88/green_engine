#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
#include "renderer/renderer.h"
#include "renderer/camera.h"
#include "renderer/renderer.h"

#define COLOR_SPLIT(vec4) (vec4.x), (vec4.y), (vec4.z), (vec4.w)

struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoord;
};

class Renderer {
public:
    Renderer();
    void init(GLFWwindow* window);
    void begin_frame(const MVP& mvp);
    //void submit(const Model& model, const Transform& transform);
    void end_frame(GLFWwindow* window );
    void shutdown();
    void render_solid_background(const glm::vec4& color);

private:
    /*
        0, 1, 3,   
        1, 2, 3
    */
     
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
    //Framebuffer m_Framebuffer;

    std::vector<Vertex> v;
    std::vector<unsigned int> indices;
    VAO vao;
    VBO vbo;
    IBO ibo;

};


#endif //RENDERER_H


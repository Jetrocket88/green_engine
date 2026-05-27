#include "renderer.h"


Renderer::Renderer()
    :v(4), vao(), vbo(), ibo()
{
    Shader shader;
    shader.load_shaders("assets/shaders/vertex.shader", "assets/shaders/fragment.shader");
    this->shaders["default"] = std::make_unique<Shader>(shader);
    this->textures["modern_baseball"] = std::make_unique<Texture>("assets/images/image.jpg", 0);

    indices.reserve(6);
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);

    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);
}

void Renderer::init(GLFWwindow* window) {
    v[0].position = glm::vec3(1.0f, 1.0f, 0.0f      );
    v[0].color =    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    v[0].texCoord = glm::vec2(1.0f, 1.0f            );

    v[1].position = glm::vec3(1.0f, -1.0f, 0.0f     );
    v[1].color =    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    v[1].texCoord = glm::vec2(1.0f, 0.0f            );

    v[2].position = glm::vec3(-1.0f, -1.0f, 0.0f    );
    v[2].color =    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    v[2].texCoord = glm::vec2(0.0f, 0.0f            );

    v[3].position = glm::vec3(-1.0f, 1.0f, 0.0f     );
    v[3].color =    glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    v[3].texCoord = glm::vec2(0.0f, 1.0f            );

    this->vao.bind();
    this->vbo.add_data(v.data(), v.size() * sizeof(Vertex));
    this->ibo.add_data(indices.data(), sizeof(indices) / sizeof(indices[0]));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, texCoord)));
    glEnableVertexAttribArray(2);

    vao.unbind();
}

void Renderer::render_solid_background(const glm::vec4& color) {
    glClearColor(COLOR_SPLIT(color));
}


void Renderer::begin_frame(const MVP& mvp) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::unique_ptr<Shader>& shader = this->shaders["default"]; 
    shader->bind();
    shader->set_mat4f("view"      , &mvp.view      );
    shader->set_mat4f("projection", &mvp.projection);
    shader->set_mat4f("model",      &mvp.model     );

    this->textures["modern_baseball"]->bind();
    this->vao.bind();
    this->ibo.bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void Renderer::end_frame(GLFWwindow* window ) { 
    glfwSwapBuffers(window);
    glfwPollEvents();    
}

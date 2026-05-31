#ifndef MODEL_H
#define MODEL_H 

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring> 
#include <chrono>

#include "vao.h"
#include "ibo.h"
#include "vbo.h"
#include "vertex.h"
#include "core/error.h"

#include "../vendor/glm/glm.hpp"

class Model {
public:
    Model();
    void init(const char* path);

    void bind()       const { return m_vao.bind();  }
    int index_count() const { return m_vertex_array.size(); }

private:
    bool load_obj_from_file(const char* path);
    

    std::vector<glm::vec3> m_out_vertices;
    std::vector<glm::vec2> m_out_uvs;
    std::vector<glm::vec3> m_out_normals;
    std::vector<Vertex>    m_vertex_array;

    int m_index_count = 0;
    VAO m_vao;
    VBO m_vbo;
    IBO m_ibo;
};

#endif //MODEL_H

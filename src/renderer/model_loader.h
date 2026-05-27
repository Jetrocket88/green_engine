#ifndef MODEL_LOAD_H
#define MODEL_LOAD_H 

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring> 

#include "../vendor/glm/glm.hpp"

class ModelLoader {
public:
static bool load_obj(
    const char* path,
    std::vector<glm::vec3> &out_vertices,
    std::vector<glm::vec2> &out_uvs,
    std::vector<glm::vec3> &out_normals
);

private:

};

#endif //MODEL_LOAD_H

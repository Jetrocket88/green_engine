#include "model.h"

bool Model::load_obj(
    const char* path,
    std::vector<glm::vec3> &out_vertices,
    std::vector<glm::vec2> &out_uvs,
    std::vector<glm::vec3> &out_normals
)  {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;

    std::string source;
    std::ifstream file;
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        file.open(path);
        std::stringstream ss;
        ss << file.rdbuf();
        source = ss.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::OBJECT_LOAD::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return false;
    }

    std::istringstream stream(source);
    std::string line;

    /*
    Vertex {
        glm::vec3 position;
        glm::vec3 normals;
        glm::vec2 texCoords;
    };
    */
    int matches = 0;

    while (std::getline(stream, line)) {
    
        if (line.find("v ") != std::string::npos) {
            glm::vec3 vertex;
            std::stringstream temp(line);
            char v = 'v';
            temp >> v >> vertex.x >> vertex.y >> vertex.z;
            temp_vertices.push_back(vertex);

        } else if (line.find("vt") != std::string::npos) {
            glm::vec2 uv;
            std::stringstream temp(line);
            std::string vt = "vt";
            temp >> vt >> uv.x >> uv.y;
            temp_uvs.push_back(uv); 

        }  else if (line.find("vn") != std::string::npos) {
            glm::vec3 normal;
            std::stringstream temp(line);
            std::string vn = "vn";
            temp >> vn >> normal.x, normal.y, normal.z;
            temp_normals.push_back(normal);

        } else if (line.find("f ") != std::string::npos) {
            int vi[3], ti[3], ni[3];

            matches = std::sscanf(
                line.c_str(),
                "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &vi[0], &ti[0], &ni[0],
                &vi[1], &ti[1], &ni[1],
                &vi[2], &ti[2], &ni[2]
            );

            if (matches != 9) {
                matches = std::sscanf(
                line.c_str(),
                "f %d//%d %d//%d %d//%d",
                &vi[0], &ni[0],
                &vi[1], &ni[1],
                &vi[2], &ni[2]
            );
                ti[0] = 0;
                ti[1] = 0;
                ti[2] = 0;
            }

            vertexIndices.push_back(vi[0]);
            vertexIndices.push_back(vi[1]);
            vertexIndices.push_back(vi[2]);
            uvIndices    .push_back(ti[0]);
            uvIndices    .push_back(ti[1]);
            uvIndices    .push_back(ti[2]);
            normalIndices.push_back(ni[0]);
            normalIndices.push_back(ni[1]);
            normalIndices.push_back(ni[2]);
        } 
    }

    for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[vertexIndex - 1];
        out_vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < uvIndices.size(); i++) {
        if (matches != 9) {
            out_uvs.push_back((glm::vec2){0, 0});
        } else {
            unsigned int uvIndex = uvIndices[i];
            glm::vec2 temp = temp_uvs[uvIndex- 1];
            out_uvs.push_back(temp);
        }
    }
    for (unsigned int i = 0; i < normalIndices.size(); i++) {
        unsigned int normalIndex = normalIndices[i];
        glm::vec3 temp = temp_normals[normalIndex - 1];
        out_normals.push_back(temp);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elsapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Elsapsed time to load model: " << path << std::endl;
    std::cout << "Was " << elsapsed.count() << "ms\n";
    return true;
}


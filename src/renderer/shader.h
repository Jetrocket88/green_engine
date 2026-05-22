#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../vendor/glm/glm.hpp"

#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"

enum ShaderType {
    VERTEX,
    FRAGMENT
};

class Shader {
private:
    void check_shader_compilation(ShaderType type);
    void check_shader_linking();

public:
    unsigned int vertexID, fragmentID, ID;
    void load_shaders(const std::string vertexPath, const std::string fragmentPath);
    void bind();

    void set_vec4f(const std::string& location, const glm::vec4& vec);
    void set_mat4f(const std::string& location, const glm::mat4* vec);


    
    Shader();




};

#endif //SHADER_H

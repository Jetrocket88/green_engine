#include "Shader.h"

Shader::Shader() {
    this->vertexID   = glCreateShader(GL_VERTEX_SHADER  );
    this->fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
}
void Shader::load_shaders(const std::string vertexPath, const std::string fragmentPath) {

    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    //std::cout << "Vertex:\n" << vShaderCode << '\n';
    //std::cout << "Fragment:\n" << fShaderCode << '\n';

    glShaderSource(this->vertexID, 1, &vShaderCode, NULL);
    glCompileShader(this->vertexID);
    check_shader_compilation(VERTEX);

    glShaderSource(this->fragmentID, 1, &fShaderCode, NULL);
    glCompileShader(this->fragmentID);
    check_shader_compilation(FRAGMENT);

    this->ID = glCreateProgram();

    glAttachShader(this->ID, this->vertexID  );
    glAttachShader(this->ID, this->fragmentID);

    glLinkProgram(this->ID);
    glUseProgram(this->ID);

    glDeleteShader(this->vertexID  );
    glDeleteShader(this->fragmentID);
}


void Shader::check_shader_compilation(ShaderType type) {
    unsigned int shader;
    if (type == VERTEX) {
        shader = this->vertexID;

    } else if (type == FRAGMENT) {
        shader = this->fragmentID;

    } else {
        //unreachable
    }

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return;
}

void Shader::check_shader_linking() {
    int  success;
    char infoLog[512];
    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER:PROGRAM:LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::bind() {
    glUseProgram(this->ID);
}


void Shader::set_vec4f(const std::string& location, const glm::vec4& vec) {
    int address = glGetUniformLocation(this->ID, location.c_str());
    this->bind();
    glUniform4f(address, vec.x, vec.y, vec.z, vec.w);
    return; 
}


void Shader::set_mat4f(const std::string& location, const glm::mat4* mat) {
    int address = glGetUniformLocation(this->ID, location.c_str());
    this->bind();
    glUniformMatrix4fv(address, 1, GL_FALSE, glm::value_ptr(*mat));

}

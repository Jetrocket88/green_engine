#include "Shader.h"

Shader::Shader() {
    this->m_vertexID   = glCreateShader(GL_VERTEX_SHADER  );
    this->m_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
}
void Shader::init(const std::string vertexPath, const std::string fragmentPath) {

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

    glShaderSource(this->m_vertexID, 1, &vShaderCode, NULL);
    glCompileShader(this->m_vertexID);
    check_shader_compilation(VERTEX);

    glShaderSource(this->m_fragmentID, 1, &fShaderCode, NULL);
    glCompileShader(this->m_fragmentID);
    check_shader_compilation(FRAGMENT);

    m_ID = glCreateProgram();

    glAttachShader(m_ID, this->m_vertexID  );
    glAttachShader(m_ID, this->m_fragmentID);

    glLinkProgram(m_ID);
    glUseProgram(m_ID);

    glDeleteShader(this->m_vertexID  );
    glDeleteShader(this->m_fragmentID);
}


void Shader::check_shader_compilation(ShaderType type) {
    unsigned int shader;
    if (type == VERTEX) { shader = this->m_vertexID; }
    else if (type == FRAGMENT) { shader = this->m_fragmentID; } 

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
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER:PROGRAM:LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::set_vec4f(const std::string& location, const glm::vec4& vec) {
    int address = glGetUniformLocation(m_ID, location.c_str());
    this->bind();
    glUniform4f(address, vec.x, vec.y, vec.z, vec.w);
    return; 
}


void Shader::set_mat4f(const std::string& location, const glm::mat4* mat) {
    int address = glGetUniformLocation(m_ID, location.c_str());
    this->bind();
    glUniformMatrix4fv(address, 1, GL_FALSE, glm::value_ptr(*mat));

}

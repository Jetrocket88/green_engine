#ifndef VAO_H
#define VAO_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VAO {
public:
    VAO();
    void init();
    void bind() const;
    void unbind() const;

private:
    unsigned int m_ID {};

};

#endif //VAO_H

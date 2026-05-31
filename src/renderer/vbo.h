#ifndef VBO_H
#define VBO_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VBO {
public:
    VBO();
    void init() {glGenBuffers(1, &m_ID); }

    void bind() const {glBindBuffer(GL_ARRAY_BUFFER, m_ID); }
    void unbind() const {glBindBuffer(GL_ARRAY_BUFFER, 0); }

    void add_data(const void* data, size_t size);

private:
    unsigned int m_ID {};

};

#endif //VBO_H


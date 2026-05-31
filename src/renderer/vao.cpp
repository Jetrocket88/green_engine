#include "vao.h"

VAO::VAO() = default;

void VAO::init() {
    glGenVertexArrays(1, &m_ID);
}

void VAO::bind() const {
    glBindVertexArray(m_ID);
}

void VAO::unbind() const {
    glBindVertexArray(0);
} 



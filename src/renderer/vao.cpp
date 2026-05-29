#include "vao.h"

VAO::VAO() = default;

void VAO::init() {
    glGenVertexArrays(1, &this->ID);
}

void VAO::bind() const {
    glBindVertexArray(this->ID);
}

void VAO::unbind() const {
    glBindVertexArray(0);
} 



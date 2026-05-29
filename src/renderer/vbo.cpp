#include "vbo.h"

VBO::VBO() = default;

void VBO::add_data(const void* data, size_t size) {
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ARRAY_BUFFER, this->ID );
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    return;
}

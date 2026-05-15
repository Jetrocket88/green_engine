#include "vbo.h"

VBO::VBO() {
}

void VBO::add_data(const float* data, size_t n) {
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ARRAY_BUFFER, this->ID );
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n, data, GL_STATIC_DRAW);
    return;
}

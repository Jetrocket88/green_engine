#include "vbo.h"

VBO::VBO() = default;

void VBO::add_data(const void* data, size_t size) {
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID );
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    return;
}

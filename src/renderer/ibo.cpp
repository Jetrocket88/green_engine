#include "ibo.h"

IBO::IBO() = default;

void IBO::init() {
    glGenBuffers(1, &m_ID);
}

void IBO::add_data(const unsigned int *data, size_t n) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, n, data, GL_STATIC_DRAW);
}

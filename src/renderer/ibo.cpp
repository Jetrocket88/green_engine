#include "ibo.h"



IBO::IBO() = default;

void IBO::init() {
    glGenBuffers(1, &this->ID);
}

void IBO::add_data(const unsigned int *data, size_t n) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * n, data, GL_STATIC_DRAW);
}

void IBO::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
}

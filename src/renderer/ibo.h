#ifndef IBO_H
#define IBO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class IBO {
public:
    IBO();
    void init();
    void add_data(const unsigned int *data, size_t n);

    void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID); }

private:
    unsigned int m_ID;

};

#endif //IBO_H


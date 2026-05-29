#ifndef VBO_H
#define VBO_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VBO {
public:
    unsigned int ID {};
    VBO();
    void init();
    void add_data(const void* data, size_t size);

private:

};

#endif //VBO_H


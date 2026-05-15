#ifndef VBO_H
#define VBO_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VBO {
public:
    unsigned int ID {};
    VBO();
    void add_data(const float* data, size_t n);



private:

};

#endif //VBO_H


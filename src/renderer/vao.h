#ifndef VAO_H
#define VAO_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VAO {
public:
    unsigned int ID {};
    VAO();
    void bind() const;
    void unbind() const;

private:

};

#endif //VAO_H

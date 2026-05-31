#ifndef ERROR_H
#define ERROR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

#endif //ERROR_H

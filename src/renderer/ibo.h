#ifndef IBO_H
#define IBO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class IBO {
public:
    unsigned int ID;
    IBO();
    void add_data(const unsigned int *data, size_t n);
    void bind() const;

private:

};

#endif //IBO_H


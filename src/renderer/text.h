#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>
#include <fstream>
#include <vector>

#include "Texture.h"
#include "Vertex.h"

class Text {
public:
    Text(const char *path);
    void render();
    void init_render();


private:
};


#endif //TEXT_H

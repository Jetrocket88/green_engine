#ifndef TEX_H
#define TEX_H

#include <iostream>
#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/shader.h"
#include "renderer/vbo.h"
#include "renderer/vao.h"
#include "renderer/ibo.h"


class Texture {
public:
    Texture(const char *path, int offset);
    Texture(uint32_t font_atlas_w, uint32_t font_atlas_h, uint8_t* font_atlas_bitmap);
    void bind();
    Texture(Texture&& other) noexcept;

private:
    int width, height, nrChannels, offset;
    unsigned char *data;
    unsigned int ID;
};

#endif //TEX_H

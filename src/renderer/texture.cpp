#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture(const char *path, int offset) {
    this->offset = offset;
    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1, &this->ID);
    glBindTexture(GL_TEXTURE_2D, this->ID);

    this->data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture :(" << std::endl;
    }
    stbi_image_free(data);
}

Texture::Texture(uint32_t font_atlas_w, uint32_t font_atlas_h, uint8_t* font_atlas_bitmap) {
    glGenTextures(1, &this->ID);
    glBindTexture(GL_TEXTURE_2D, this->ID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, font_atlas_w, font_atlas_h, 0, GL_RED, GL_UNSIGNED_BYTE, font_atlas_bitmap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0 + this->offset);
    glBindTexture(GL_TEXTURE_2D, this->ID);
}


Texture::Texture(Texture&& other) noexcept {
    this->width = other.width;
    this->height= other.height;
    this->nrChannels = other.nrChannels;
    this->offset= other.offset;
    this->data = other.data;
    this->ID = other.ID;
    other.data = nullptr;
    std::cout << "Move constructor called ?\n";

}

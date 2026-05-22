#include "text.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Text::Text(const char *path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("Failed to open font: " + std::string(path));
    }
    file.seekg(0, std::ios::end); //go to the end of the file
    auto&& size = file.tellg();   //tell me how far you travelled
    file.seekg(0, std::ios::beg); //go back to the beginning

    uint8_t* font_buffer = new uint8_t[static_cast<size_t>(size)];

    file.read((char *)font_buffer, size);
    int32_t font_count = stbtt_GetNumberOfFonts(font_buffer);
    if (font_count == -1) {
        std::cerr << "The font file doesn't correspond to the valid font data\n";
    } else {
        std::cout << "The file " << std::string(path) << " contains " << font_count << " fonts\n";
    }
    
    uint32_t font_atlas_w = 1024;
    uint32_t font_atlas_h = 1024;
    
    uint8_t *font_atlas_bitmap = new uint8_t[font_atlas_h * font_atlas_h];

    const uint32_t code_point_of_first_char = 32;
    const uint32_t chars_to_include_in_font_atlas = 95;

    float font_size= 64.0f;

    stbtt_packedchar packed_chars[chars_to_include_in_font_atlas];
    stbtt_aligned_quad aligned_quads[chars_to_include_in_font_atlas];

    stbtt_pack_context ctx;
    stbtt_packedchar *char_array = (stbtt_packedchar*)malloc(sizeof(stbtt_packedchar) * chars_to_include_in_font_atlas);
    
    stbtt_PackBegin(
        &ctx,
        (unsigned char *)font_atlas_bitmap,
        font_atlas_w,
        font_atlas_h,
        0,
        1,
        nullptr
    );

    stbtt_PackFontRange(
        &ctx,
        font_buffer,
        0,
        font_size,
        code_point_of_first_char,
        chars_to_include_in_font_atlas,
        packed_chars
    );
    stbtt_PackEnd(&ctx);
    for (int i = 0; i < chars_to_include_in_font_atlas; i++) {
        float unused_x, unused_y;
        stbtt_GetPackedQuad(
            char_array,
            font_atlas_w,
            font_atlas_h,
            i,
            &unused_x, 
            &unused_y,
            &aligned_quads[i],
            0
        );
    }
    
    delete[] font_atlas_bitmap;
    delete[] font_buffer;
}


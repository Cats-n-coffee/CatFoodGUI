#define STB_IMAGE_IMPLEMENTATION
#include "../vendors/stb_image.h"
#include "Texture2DPNG.h"

unsigned int generateTexture2DPNG(const std::string& filePath)
{
    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int imageWidth, imageHeight, nrChannel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imageData = stbi_load(filePath.c_str(), &imageWidth, &imageHeight, &nrChannel, 0);

    if (imageData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(imageData);

    return texture;
}

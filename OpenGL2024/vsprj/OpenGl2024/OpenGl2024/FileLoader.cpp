#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "FileLoader.h"

unsigned int FileLoader::LoadTextures(const char* filePath, int comp)
{
    unsigned int textureId = 0;
    glGenTextures(1, &textureId);
    //std::cout << filePath << " txtID: " << textureId << std::endl; //debugging voor textures
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, numChannels;
    unsigned char* data = stbi_load(filePath, &width, &height, &numChannels, comp);

    if (data != NULL)
    {
        if (comp != 0) numChannels = comp;

        switch (numChannels)
        {
        case (1):  // Grayscale image (single channel)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
            break;
        }
        case (3):
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        }
        case (4):
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
        }
        default:
        {
            std::cout << "Unsupported number of channels: " << numChannels << std::endl;
            break;
        }
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed To Load Texture: " << filePath << std::endl;
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return textureId;
}
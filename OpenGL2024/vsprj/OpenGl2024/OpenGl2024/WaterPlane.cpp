#include "WaterPlane.h"
#include <iostream>


void WaterPlane::DebugVertexData() const {
    std::cout << "Water plane vertex count: " << vertices.size() / 5 << std::endl;
    std::cout << "Water plane index count: " << indices.size() << std::endl;

    // Print de eerste paar vertices
    for (int i = 0; i < std::min(5, static_cast<int>(vertices.size() / 5)); ++i) {
        std::cout << "Vertex " << i << ": "
            << vertices[i * 5] << ", "
            << vertices[i * 5 + 1] << ", "
            << vertices[i * 5 + 2] << " | "
            << vertices[i * 5 + 3] << ", "
            << vertices[i * 5 + 4] << std::endl;
    }
}

unsigned int WaterPlane::GeneratePlane(const char* heightmap, GLenum format, int comp, float hScale, float xzScale, unsigned int& indexCount, unsigned int& heightmapID) {
    int width, height, channels;
    unsigned char* data = nullptr;
    if (heightmap != nullptr) {
        data = stbi_load(heightmap, &width, &height, &channels, comp);
        if (data) {
            glGenTextures(1, &heightmapID);
            glBindTexture(GL_TEXTURE_2D, heightmapID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    int stride = 8;
    float* vertices = new float[(width * height) * stride];
    unsigned int* indices = new unsigned int[(width - 1) * (height - 1) * 6];

    int index = 0;
    for (int i = 0; i < (width * height); i++) {
        // TODO: calculate x/z values
        int x = i % width;
        int z = i / width;

        // TODO: set position
        vertices[index++] = x * xzScale;
        vertices[index++] = 0;
        vertices[index++] = z * xzScale;

        // TODO: set normal
        vertices[index++] = 0;
        vertices[index++] = 1;
        vertices[index++] = 0;

        // TODO: set uv
        vertices[index++] = x / (float)width;
        vertices[index++] = z / (float)height;
    }

    // OPTIONAL TODO: Calculate normal
    // TODO: Set normal

    index = 0;
    for (int i = 0; i < (width - 1) * (height - 1); i++) {
        int x = i % (width - 1);
        int z = i / (width - 1);

        int vertex = z * width + x;

        indices[index++] = vertex;
        indices[index++] = vertex + width;
        indices[index++] = vertex + width + 1;

        indices[index++] = vertex;
        indices[index++] = vertex + width + 1;
        indices[index++] = vertex + 1;
    }

    unsigned int vertSize = (width * height) * stride * sizeof(float);
    indexCount = ((width - 1) * (height - 1) * 6);

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // vertex information!
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride, 0);
    glEnableVertexAttribArray(0);
    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    // uv
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    delete[] vertices;
    delete[] indices;

    stbi_image_free(data);

    return VAO;
}
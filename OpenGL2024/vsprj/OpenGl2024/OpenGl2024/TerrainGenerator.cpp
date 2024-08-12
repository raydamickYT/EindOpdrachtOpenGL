#include "TerrainGenerator.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "perlin_noise.hpp"

void TerrainGenerator::generateTerrain(const glm::vec3 position, const int size, float hScale, float xzScale, glm::vec3 offset) {
    const int stride = 3;  // Alleen positie-gegevens
    int count = size * size;
    const int gridSize = 400;
    const int octaves = 8;

    std::vector<float> vertices(count * stride);
    std::vector<unsigned int> indices((size - 1) * (size - 1) * 6);

    // Vereenvoudigde vertex generatie zonder multi-threading
    for (int i = 0; i < count; ++i) {
        int x = i % size;
        int z = i / size;

        float globalX = x * xzScale;
        float globalZ = z * xzScale;

        int vertexIndex = i * stride;

        if (vertexIndex + 2 < vertices.size()) {
            vertices[vertexIndex] = globalX;
			float perlinValue = perlin_noise::octaved_perlin_noise(globalX + offset.x, globalZ + offset.z, octaves, gridSize);
            vertices[vertexIndex + 1] = perlinValue * hScale;
            vertices[vertexIndex + 2] = globalZ;
        }
        else {
            std::cerr << "Error: Vertex index out of range: " << vertexIndex << std::endl;
            std::cerr << "Vertices size: " << vertices.size() << std::endl;
        }
    }


    // Genereren van de indices voor het terrein
    unsigned int index = 0;
    for (unsigned int i = 0; i < (size - 1) * (size - 1); ++i) {
        int x = i % (size - 1);
        int z = i / (size - 1);

        int vertex = z * size + x;

        if (vertex + size + 1 < vertices.size() / stride) {
            indices[index++] = vertex;
            indices[index++] = vertex + size;
            indices[index++] = vertex + size + 1;
            indices[index++] = vertex;
            indices[index++] = vertex + size + 1;
            indices[index++] = vertex + 1;
        }
        else {
            std::cerr << "Error: Attempted to access out-of-range index at vertex " << vertex << std::endl;
        }
    }

    // Proces om het terrein te visualiseren
    processPlane(position, indices, vertices);
}

void TerrainGenerator::processPlane(const glm::vec3 position, const std::vector<unsigned int>& indices, const std::vector<float>& vertices) {
    const int stride = 3;  // Alleen positie-gegevens
    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Hier visualiseren we het terrein door gebruik te maken van glDrawElements
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Optioneel: Opruimen van buffers, dit zou je ook later kunnen doen als het tekenproces volledig is
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


unsigned int TerrainGenerator::GeneratePlane(const char* heightmap, GLenum format, int comp, float hScale, float xzScale, unsigned int& indexCount, unsigned int& heightmapID) 
{
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
        //TODO: calc x/z values
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
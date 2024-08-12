#ifndef WATER_PLANE_H
#define WATER_PLANE_H

#include <vector>
#include <map>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>


class WaterPlane {
public:
    unsigned int VAO, VBO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    unsigned int GeneratePlane(const char* heightmap, GLenum format, int comp, float hScale, float xzScale, unsigned int& indexCount, unsigned int& heightmapID);

    void DebugVertexData() const;


    WaterPlane(float width, float depth) {
    }

    ~WaterPlane() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void Draw() {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};
#endif

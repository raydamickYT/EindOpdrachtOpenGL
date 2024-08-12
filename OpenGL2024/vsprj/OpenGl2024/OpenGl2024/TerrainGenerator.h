#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <thread>
#include "ThreadPool.h"
#include "Renderer.h"

struct vec2compare
{
    bool operator()(const glm::vec2& a, const glm::vec2& b) const
    {
        if (a.x != b.x)
            return a.x < b.x;
        return a.y < b.y;
    }
};

class TerrainGenerator {
public:
    TerrainGenerator() {}
    ~TerrainGenerator() {}

    void initialize(ThreadPool& threadPool);
    void generateTerrain(const glm::vec3 position, const int size, float hScale, float xzScale, glm::vec3 offset);
    void checkVisiblePlanes(WorldInformation& worldInfo, std::map<glm::vec2, Plane, vec2compare>& activeTerrainChunks);
    void processPlane(const glm::vec3 position, const std::vector<unsigned int>& indices, const std::vector<float>& vertices);
    unsigned int GeneratePlane(const char* heightmap, GLenum format, int comp, float hScale, float xzScale, unsigned int& indexCount, unsigned int& heightmapID);
    void renderTerrain();

private:

    const int maxViewDistance = 400;
    const int chunkSize = 241;
    const int xScale = 5;
    int systemThreadsCount;
    ThreadPool* threadPool;
    std::map<glm::vec2, Plane, vec2compare>* activeTerrainChunks2;

    static glm::vec3 getVertex(const std::vector<float>& vertices, const int width, const int x, const int z, const int stride);
    static void calculateNormals(std::vector<float>& vertices, const int stride, const int height, const int width);
};

#endif // TERRAIN_GENERATOR_H
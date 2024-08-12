#ifndef WATERFRAMEBUFFERS_H
#define WATERFRAMEBUFFERS_H

#include "ModelLoader.h"


class WaterFrameBuffers {
public:
    WaterFrameBuffers(int windowWidth, int windowHeight);
    ~WaterFrameBuffers();

    void bindReflectionFrameBuffer();
    void bindRefractionFrameBuffer();
    void unbindCurrentFrameBuffer();

    GLuint getReflectionTexture();
    GLuint getRefractionTexture();
    GLuint getRefractionDepthTexture();

private:
    static const int REFLECTION_WIDTH = 320;
    static const int REFLECTION_HEIGHT = 180;

    static const int REFRACTION_WIDTH = 1280;
    static const int REFRACTION_HEIGHT = 720;

    GLuint reflectionFrameBuffer;
    GLuint reflectionTexture;
    GLuint reflectionDepthBuffer;

    GLuint refractionFrameBuffer;
    GLuint refractionTexture;
    GLuint refractionDepthTexture;

    int windowWidth, windowHeight;

    void initialiseReflectionFrameBuffer();
    void initialiseRefractionFrameBuffer();
    void bindFrameBuffer(GLuint frameBuffer, int width, int height);
    GLuint createFrameBuffer();
    GLuint createTextureAttachment(int width, int height);
    GLuint createDepthTextureAttachment(int width, int height);
    GLuint createDepthBufferAttachment(int width, int height);
};

#endif // WATERFRAMEBUFFERS_H

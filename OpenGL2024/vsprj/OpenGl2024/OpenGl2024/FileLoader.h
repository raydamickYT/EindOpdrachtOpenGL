#pragma once

#include <functional>
#include <thread>
#include <GLAD/glad.h>

#include <iostream>
#include <future>
#include <fstream>

static class FileLoader
{
public:
	static unsigned int LoadTextures(const char* filePath, int comp = 0);
};
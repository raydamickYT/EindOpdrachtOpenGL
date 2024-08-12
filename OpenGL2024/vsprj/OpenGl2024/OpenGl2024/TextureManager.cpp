#include "TextureManager.h"

void TextureManager::LoadTextures(Renderer& renderer, GLuint program, std::string nameProgram, Cube& cube)
{
	//Textures for the terrain.
	if (renderer.dirt == 0) 
	{
		renderer.dirt = FileLoader::LoadTextures("Textures/dirt.jpg");
		renderer.sand = FileLoader::LoadTextures("Textures/sand.jpg");
		renderer.grass = FileLoader::LoadTextures("Textures/grass.png", 4);
		renderer.rock = FileLoader::LoadTextures("Textures/rock.jpg");
		renderer.snow = FileLoader::LoadTextures("Textures/snow.jpg");
		renderer.mainTex = FileLoader::LoadTextures("Textures/Heightmap.png");
		renderer.normalTex = FileLoader::LoadTextures("Textures/HeightmapNormal.png");
		//renderer.waterTex = FileLoader::LoadTextures("Textures/blue.jpg");
		//renderer.ReflTex = FileLoader::LoadTextures("Textures/dirt.jpg");
	}

	if (program != NULL && nameProgram == "water")
	{
		cout << "load water textures" << endl;
		glUseProgram(program);

		glUniform1i(glGetUniformLocation(program, "normalTexture"), 0);
		glUniform1i(glGetUniformLocation(program, "projectedTexture"), 1);
	}

	if (program != NULL && nameProgram == "terrain")
	{
		glUseProgram(program);

		glUniform1i(glGetUniformLocation(program, "dirt"), 0);
		glUniform1i(glGetUniformLocation(program, "sand"), 1);
		glUniform1i(glGetUniformLocation(program, "grass"), 2);
		glUniform1i(glGetUniformLocation(program, "rock"), 3);
		glUniform1i(glGetUniformLocation(program, "snow"), 4);
		//glUniform1i(glGetUniformLocation(program, "mainTex"), 2);
		glUniform1i(glGetUniformLocation(program, "normalTex"), 5);
	}

	if (program != NULL && nameProgram == "model")
	{
		//Texture setup for the models.
		glUseProgram(program);

		glUniform1i(glGetUniformLocation(program, "texture_diffuse1"), 0);
		glUniform1i(glGetUniformLocation(program, "texture_specular1"), 1);
		glUniform1i(glGetUniformLocation(program, "texture_normal1"), 2);
		glUniform1i(glGetUniformLocation(program, "texture_roughness1"), 3);
		glUniform1i(glGetUniformLocation(program, "texture_ao1"), 4);
	}

	//Textures for the Box.
	auto cubeDiffuse = FileLoader::LoadTextures("Textures/container2.png");
	auto cubeNormal = FileLoader::LoadTextures("Textures/container2_normal.png");

	cube.Textures.push_back(cubeDiffuse);
	cube.Textures.push_back(cubeNormal);
}
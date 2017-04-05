#pragma once

#include <vector>
#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "../glHelper.h"
#include "ModelData.h"
#include "../particles//ParticleData.h"

#ifdef _WIN32
#define SURFACE_VERT_SHADER_PATH "../../src/shaders/simple.vert"
#define SURFACE_FRAG_SHADER_PATH "../../src/shaders/simple.frag"
#elif __unix__
#define SURFACE_VERT_SHADER_PATH "../src/shaders/simple.vert"
#define SURFACE_FRAG_SHADER_PATH "../src/shaders/simple.frag"
#endif

class ModelRenderer
{
public:
	ModelRenderer();
	~ModelRenderer();

	GLuint simpleShader;
	GLuint vao;
	GLuint vbo;
    GLuint nbo;
    GLuint ibo;
    unsigned int *particleCount;

	void init();
	void render(ParticleData &particles, ModelData &data, glm::mat4 &modelViewProjectionMatrix, glm::mat4 &modelViewMatrix, glm::vec3 &viewSpaceLightPosition, glm::mat4 &projectionMatrix);
};

#include "SDL.h"
#include "EngineFramework/Window.h"
#include "EngineFramework/GLLogging.h"
#include "GL/glew.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include <iostream>
#include <cstddef>
#include <spine/Atlas.h>
#include <spine/Skeleton.h>
#include <spine/SkeletonData.h>
#include <spine/SkeletonBinary.h>
#include <spine/SkeletonJson.h>
#include <spine/Slot.h>
#include <spine/Attachment.h>
#include <spine/RegionAttachment.h>
#include <spine/AtlasAttachmentLoader.h>
#include <GLM\gtc\matrix_transform.hpp>

struct Position
{
	float x, y;
};

struct UVs
{
	float u, v;
};

struct Color
{
	float r, g, b, a;
};


// A single vertex with UV 
typedef struct Vertex {
	// Position in x/y plane
	Position position{ 0.0f, 0.0f };

	// UV coordinates
	UVs uvs{ 0.0f, 0.0f };

	//Don't care about color right now so just using default values
	Color color{ 0.1f, 0.1f, 0.1f, 1.0f };
} Vertex;

const uint16 maxVerticesPerAttachment = 2048;
float worldVerticesPositions[maxVerticesPerAttachment];
Vertex vertices[maxVerticesPerAttachment];



void addVertex(float x, float y, float u, float v, int* index) {
	Vertex* vertex = &vertices[*index];
	vertex->position.x = x;
	vertex->position.y = y;
	vertex->uvs.u = u;
	vertex->uvs.v = v;
	vertex->color.r = .1f;
	vertex->color.g = .1f;
	vertex->color.b = .1f;
	vertex->color.a = 1.0f;
	*index += 1;
}

Blz::Window window;

enum class GameState
{
	PLAY,
	EXIT
};

int main(int agrc, char** argv)
{
	window.Initialize();

	Blz::Graphics::ShaderProgram colorShaderProgram;

	colorShaderProgram.Init("Source/Shaders/VertexShader.glsl", "Source/Shaders/FragmentShader.glsl");
	colorShaderProgram.Compile();
	colorShaderProgram.AddAttribute("vertexPosition");
	colorShaderProgram.AddAttribute("textCoord");
	colorShaderProgram.AddAttribute("color");
	colorShaderProgram.Link();
	colorShaderProgram.Bind();

	GLuint uniformLocation = colorShaderProgram.GetUniformLocation("basicTexture");
	glUniform1i(uniformLocation, 0);

	spAtlas* atlas = spAtlas_createFromFile("spineboy.atlas", 0);

	spSkeletonBinary* json = spSkeletonBinary_create(atlas);

	spSkeletonData* skeletonData = spSkeletonBinary_readSkeletonDataFile(json, "spineboy-ess.skel");

	spSkeletonBinary_dispose(json);

	spSkeleton* skeleton = spSkeleton_create(skeletonData);

	skeleton->x = 500.0f;
	skeleton->y = 100.0f;

	spSkeleton_setBonesToSetupPose(skeleton);
	spSkeleton_updateWorldTransform(skeleton);

	spBone* bone = spSkeleton_findBone(skeleton, "front-fist");
	spSlot* slot = spSkeleton_findSlot(skeleton, "front-fist");

	spAttachment* attachment = slot->attachment;

	spRegionAttachment* regionAttachment = (spRegionAttachment*)attachment;

	Blz::Graphics::Texture* texture = nullptr;

	texture = (Blz::Graphics::Texture*)((spAtlasRegion*)regionAttachment->rendererObject)->page->rendererObject;

	spRegionAttachment_computeWorldVertices(regionAttachment, bone, worldVerticesPositions, 0, 2);

	int index = 0;

	addVertex(worldVerticesPositions[0], worldVerticesPositions[1], regionAttachment->uvs[0], regionAttachment->uvs[1], &index);
	addVertex(worldVerticesPositions[2], worldVerticesPositions[3], regionAttachment->uvs[2], regionAttachment->uvs[3], &index);
	addVertex(worldVerticesPositions[4], worldVerticesPositions[5], regionAttachment->uvs[4], regionAttachment->uvs[5], &index);
	addVertex(worldVerticesPositions[4], worldVerticesPositions[5], regionAttachment->uvs[4], regionAttachment->uvs[5], &index);
	addVertex(worldVerticesPositions[6], worldVerticesPositions[7], regionAttachment->uvs[6], regionAttachment->uvs[7], &index);
	addVertex(worldVerticesPositions[0], worldVerticesPositions[1], regionAttachment->uvs[0], regionAttachment->uvs[1], &index);

	GLuint vboID;

	glm::mat4 ortho = glm::ortho<float>(0.0f, static_cast<float>(1024), 0.0f, static_cast<float>(768));

	GLuint transformationMatrixUniformLocation = colorShaderProgram.GetUniformLocation("transformMatrix");

	glm::mat4 transformationMatrix = glm::translate(ortho, glm::vec3{ 0.0f, 0.0f, 0.0f });
	glUniformMatrix4fv(transformationMatrixUniformLocation, 1, GL_FALSE, &(transformationMatrix[0][0]));

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBindTexture(GL_TEXTURE_2D, texture->GetID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uvs));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	window.SwapBuffers();

	GameState gamestate{ GameState::PLAY };

	SDL_Event evnt;

	while (gamestate != GameState::EXIT)
	{
		unsigned int startTime = SDL_GetTicks();

		//Game Logic Update
		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
			case SDL_QUIT:
				gamestate = GameState::EXIT;

			default:
				break;
			}
		}

		

	}

	return 0;
}

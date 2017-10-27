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

const uint16 maxVerticesPerAttachment = 2048;
float worldVerticesPositions[maxVerticesPerAttachment];

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

	// Color, each channel in the range from 0-1
	// (Should really be a 32-bit RGBA packed color)
	Color color{ 0.1f, 0.1f, 0.1f, 1.0f };
} Vertex;

Vertex vertices[maxVerticesPerAttachment];

void addVertex(float x, float y, float u, float v, float r, float g, float b, float a, int* index) {
	Vertex* vertex = &vertices[*index];
	vertex->position.x = x;
	vertex->position.y = y;
	vertex->uvs.u = u;
	vertex->uvs.v = v;
	vertex->color.r = r;
	vertex->color.g = g;
	vertex->color.b = b;
	vertex->color.a = a;
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

	RUNTIME_ASSERT(atlas != nullptr, "Atlas not loading properly!");

	spSkeletonJson* json = spSkeletonJson_create(atlas);

	spSkeletonData* skeletonData = spSkeletonJson_readSkeletonDataFile(json, "spineboy-ess.json");

	if (!skeletonData)
	{
		LOG("%s\n", json->error);
		spSkeletonJson_dispose(json);
	};

	spSkeletonJson_dispose(json);

	spSkeleton* skeleton = spSkeleton_create(skeletonData);

	skeleton->x = 500.0f;
	skeleton->y = 200.0f;

	spSkeleton_updateWorldTransform(skeleton);

	Blz::Graphics::Texture* texture = nullptr;

	for (int i = 0; i < 20; ++i)
	{
		spSlot* slot = skeleton->drawOrder[i];

		RUNTIME_ASSERT(slot != nullptr, "Slot not loaded properly!");

		spAttachment* attachment = slot->attachment;

		if (!attachment) continue;

		int vertexIndex = 0;
		if (attachment->type == SP_ATTACHMENT_REGION)
		{
			spRegionAttachment* regionAttachment = (spRegionAttachment*)attachment;

			texture = (Blz::Graphics::Texture*)((spAtlasRegion*)regionAttachment->rendererObject)->page->rendererObject;

			spRegionAttachment_computeWorldVertices(regionAttachment, slot->bone, worldVerticesPositions, 0, 2);

			addVertex(worldVerticesPositions[0],
				worldVerticesPositions[1],
				regionAttachment->uvs[0],
				regionAttachment->uvs[1], 0.1, 0.1, 0.1, 1.0, &vertexIndex);

			addVertex(worldVerticesPositions[2],
				worldVerticesPositions[3],
				regionAttachment->uvs[2],
				regionAttachment->uvs[3], 0.1, 0.1, 0.1, 1.0, &vertexIndex);

			addVertex(worldVerticesPositions[4],
				worldVerticesPositions[5],
				regionAttachment->uvs[4],
				regionAttachment->uvs[5], 0.1, 0.1, 0.1, 1.0, &vertexIndex);

			addVertex(worldVerticesPositions[4],
				worldVerticesPositions[5],
				regionAttachment->uvs[4],
				regionAttachment->uvs[5], 0.1, 0.1, 0.1, 1.0, &vertexIndex);

			addVertex(worldVerticesPositions[6],
				worldVerticesPositions[7],
				regionAttachment->uvs[6],
				regionAttachment->uvs[7], 0.1, 0.1, 0.1, 1.0, &vertexIndex);

			addVertex(worldVerticesPositions[0],
				worldVerticesPositions[1],
				regionAttachment->uvs[0],
				regionAttachment->uvs[1], 0.1, 0.1, 0.1, 1.0, &vertexIndex);
		}

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
	};

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

		

		window.SwapBuffers();
	}

	return 0;
}

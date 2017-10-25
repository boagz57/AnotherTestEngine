#include "SDL.h"
#include "EngineFramework/Window.h"
#include "EngineFramework/GLLogging.h"
#include "GL/glew.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include <iostream>
#include <spine/Atlas.h>
#include <spine/Skeleton.h>
#include <spine/SkeletonData.h>
#include <spine/SkeletonBinary.h>
#include <spine/SkeletonJson.h>
#include <spine/Slot.h>
#include <spine/Attachment.h>
#include <spine/RegionAttachment.h>
#include <spine/AtlasAttachmentLoader.h>

const uint16 maxVerticesPerAttachment = 2048;
float worldVerticesPositions[maxVerticesPerAttachment];

// A single vertex with UV 
typedef struct Vertex {
	// Position in x/y plane
	float x, y;

	// UV coordinates
	float u, v;

	// Color, each channel in the range from 0-1
	// (Should really be a 32-bit RGBA packed color)
	float r, g, b, a;
} Vertex;

Vertex vertices[maxVerticesPerAttachment];

void addVertex(float x, float y, float u, float v, float r, float g, float b, float a, int* index) {
	Vertex* vertex = &vertices[*index];
	vertex->x = x;
	vertex->y = y;
	vertex->u = u;
	vertex->v = v;
	vertex->r = r;
	vertex->g = g;
	vertex->b = b;
	vertex->a = a;
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

	colorShaderProgram.Init("Source/GameEngine/Shaders/VertexShader.glsl", "Source/GameEngine/Shaders/FragmentShader.glsl");
	colorShaderProgram.Compile();
	colorShaderProgram.AddAttribute("vertexPosition");
	colorShaderProgram.AddAttribute("textCoord");
	colorShaderProgram.Link();
	colorShaderProgram.Bind();

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

	spSkeleton_updateWorldTransform(skeleton);

	spSlot* slot = skeleton->drawOrder[0];

	RUNTIME_ASSERT(slot != nullptr, "Slot not loaded properly!");

	spAttachment* attachment = slot->attachment;

	Blz::Graphics::Texture* texture = nullptr;
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

		GLuint vboID;

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBindTexture(GL_TEXTURE0, texture->GetID());
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);//Add offsetof() for stride parameter

		window.ClearBuffers();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.SwapBuffers();
	}

	return 0;
}

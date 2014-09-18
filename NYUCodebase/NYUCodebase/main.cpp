#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <vector>
#include "Entity.h"

using namespace std;

SDL_Window* displayWindow;

typedef struct {
	float x;
	float y;
	float r;
	float g;
	float b;
} Vertex2D;

GLuint LoadTexture(const char *image_path)
{
	SDL_Surface *surface = IMG_Load(image_path);
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);
	return textureID;
}

void DrawSprite(GLint texture, float x, float y, float width, float height, float rotation)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0);
	glRotatef(rotation, 0.0, 0.0, 1.0);
	GLfloat quad[] = { -width / 2.0f, height / 2.0f, -width / 2.0f, -height / 2.0f, width / 2.0f, -height / 2.0f, width / 2.0f, height / 2.0f};
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat quadUVs[] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 }; 
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
}

void drawQuad(float x, float y, float width, float height)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0);
	Vertex2D quadData[4] = { { -width, height, 1.0f, 1.0f, 1.0f }, { -width, -height, 1.0f, 1.0f, 1.0f }, { width, -height, 1.0f, 1.0f, 1.0f }, { width, height, 1.0f, 1.0f, 1.0f } };
	glVertexPointer(4, GL_FLOAT, sizeof(float) * 5, quadData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &quadData[0].r);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
}

void drawNet()
{
	for (float i = 0.8f; i > -0.9f; i -= 0.1f)
	{
		drawQuad(0.0f, i, 0.025f, 0.025f);
	}
}

void drawQuadLine(float x, float y, float width, float height)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0);
	Vertex2D quadData[4] = { { -width, height, 1.0f, 1.0f, 1.0f }, { -width, -height, 1.0f, 1.0f, 1.0f }, { width, -height, 1.0f, 1.0f, 1.0f }, { width, height, 1.0f, 1.0f, 1.0f } };
	glVertexPointer(4, GL_FLOAT, sizeof(float) * 5, quadData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &quadData[0].r);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
}

void setup()
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
}

void render(float elapsed, vector<Entity*> entities, bool isWinner, GLuint winner)
{
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	drawQuadLine(0.0f, 0.8f, 1.30f, .025f);
	drawQuadLine(0.0f, -0.8f, 1.30f, .025f);
	drawNet();

	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->drawByQuad();
	}

	if (isWinner)
	{
		DrawSprite(winner, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	}

	SDL_GL_SwapWindow(displayWindow);
}

void paddleMovementControls(const Uint8 *keys, vector<Entity*> entities)
{
	if (keys[SDL_SCANCODE_W] == 1)
	{
		if (entities[0]->y <= 0.7f)
		{
			entities[0]->direction_y = 1.0f;
		}
	}
	else if (keys[SDL_SCANCODE_S] == 1)
	{
		if (entities[0]->y >= -0.7f)
		{
			entities[0]->direction_y = -1.0f;
		}
	}
	if (keys[SDL_SCANCODE_UP] == 1)
	{
		if (entities[1]->y <= 0.7f)
		{
			entities[1]->direction_y = 1.0f;
		}
	}
	else if (keys[SDL_SCANCODE_DOWN] == 1)
	{
		if (entities[1]->y >= -0.7f)
		{
			entities[1]->direction_y = -1.0f;
		}
	}
}

bool processEvents(SDL_Event &event, const Uint8 *keys, vector<Entity*> entities)
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			return false;
		}
	}
	paddleMovementControls(keys, entities);
}

void update(float elapsed, vector<Entity*> entities, int &p1, int &p2, bool &isWinner)
{
	entities[2]->checkVerticalWallCollision();
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->move(elapsed);

		if (i < 2)
		{
			if (entities[2]->checkEntitytoEntityCollision(entities[i]))
			{
				entities[2]->direction_x *= -1.0f;
			}
			entities[i]->direction_y = 0;
		}
	}
	if (entities[2]->x <= -1.27f)
	{
		p2 += 1;
		entities[2]->x = 0.0f;
		entities[2]->y = 0.0f;
		if (p2 == 5)
		{
			entities[2]->speed = 0.0f;
			isWinner = true;
		}
	}
	if (entities[2]->x >= 1.27f)
	{
		p1 += 1;
		entities[2]->x = 0.0f;
		entities[2]->y = 0.0f;
		if (p1 == 5)
		{
			entities[2]->speed = 0.0f;
			isWinner = true;
		}
	}
}

int main(int argc, char *argv[])
{
	SDL_Event event;
	setup();

	float lastFrameTicks = 0.0f;
	int playerLeftScore = 0;
	int playerRightScore = 0;
	bool isWinner = false;
	Entity *playerLeft = new Entity(-1.27f, 0.0f, 0.0f, NULL, 0.05f, 0.2f, 0.75f, 0.0f, 0.0f);
	Entity *playerRight = new Entity(1.27f, 0.0f, 0.0f, NULL, 0.05f, 0.2f, 0.75f, 0.0f, 0.0f);
	Entity *ball = new Entity(0.0f, 0.0f, 0.0f, NULL, 0.05f, 0.05f, 0.5f, 1.0f, 1.0f);

	vector<Entity*> entities;
	entities.push_back(playerLeft);
	entities.push_back(playerRight);
	entities.push_back(ball);
	GLuint winnerTexture = LoadTexture("winner.png");

	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	while (processEvents(event, keys, entities)) {
		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks; 
		//rotation += 45.0f * elapsed;

		update(elapsed, entities, playerLeftScore, playerRightScore, isWinner);
		render(elapsed, entities, isWinner, winnerTexture);
	}

	SDL_Quit();
	return 0;
}
#pragma once
#include <stdlib.h>
#include <vector>
#include <string>
#include "DrawingManager.h"

DrawingManager::DrawingManager()
{
	//fontTexture = LoadTexture("font1.png");
	spriteSheetTexture = LoadTexture("arne_sprites.png");
}
DrawingManager::~DrawingManager()
{

}

/*void DrawingManager::DrawBullet(Bullet* bullet)
{
	/*if (!(bullet->isVisible()))
	{
	return;
	}*\

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(bullet->getX(), bullet->getY(), 0.0f);
	glRotated(bullet->getAngle(), 0.0f, 0.0f, 1.0f);
	Vertex2D quadData[4] = {
			{ -bullet->getSize(), bullet->getSize(), 1.0f, 1.0f, 1.0f },
			{ -bullet->getSize(), -bullet->getSize(), 1.0f, 1.0f, 1.0f },
			{ bullet->getSize(), -bullet->getSize(), 1.0f, 1.0f, 1.0f },
			{ bullet->getSize(), bullet->getSize(), 1.0f, 1.0f, 1.0f }
	};
	glVertexPointer(4, GL_FLOAT, sizeof(float) * 5, quadData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &quadData[0].r);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
}*/

void DrawingManager::DrawQuad(float width, float height, float r, float g, float b)
{
	Vertex2D quadData[4] = {
			{ -width / 2.0f, height / 2.0f, r, g, b },
			{ -width / 2.0f, -height / 2.0f, r, g, b },
			{ width / 2.0f, -height / 2.0f, r, g, b },
			{ width / 2.0f, height / 2.0f, r, g, b }
	};
	glVertexPointer(2, GL_FLOAT, sizeof(float) * 5, quadData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &quadData[0].r);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
}

void DrawingManager::DrawTriangle(float width, float height)
{
	Vertex2D quadData[3] = {
			{ -width / 2.0f, -height / 2.0f, 1.0f, 1.0f, 1.0f },
			{ width / 2.0f, -height / 2.0f, 1.0f, 1.0f, 1.0f },
			{ 0.0f, height / 2.0f, 1.0f, 1.0f, 1.0f }
	};
	glVertexPointer(2, GL_FLOAT, sizeof(float) * 5, quadData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &quadData[0].r);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
}


GLuint DrawingManager::LoadTexture(const char *img_path)
{
	SDL_Surface *surface = IMG_Load(img_path);
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);
	return textureID;
}

void DrawingManager::DrawSheetSpriteUniform(float width, float height, int index)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteSheetTexture);

	GLfloat quad[] = { -width, height, -width, -height, width, -height, width, height };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);
	float u = (float)(((int)index) % SPRITE_COUNT_X) / (float)SPRITE_COUNT_X;
	float v = (float)(((int)index) / SPRITE_COUNT_X) / (float)SPRITE_COUNT_Y;
	float spriteWidth = 1.0 / (float)SPRITE_COUNT_X;
	float spriteHeight = 1.0 / (float)SPRITE_COUNT_Y;
	GLfloat quadUVs[] = {	
							u, v,
							u, v + spriteHeight,
							u + spriteWidth, v + spriteHeight,
							u + spriteWidth, v
						};
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
}
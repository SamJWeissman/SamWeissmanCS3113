#pragma once
#include <stdlib.h>
#include <vector>
#include <string>
#include "DrawingManager.h"
#include "Entity.h"

DrawingManager::DrawingManager()
{
	fontTexture = LoadTexture("font1.png");
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

void DrawingManager::DrawQuad(float width, float height, float x, float y, float r, float g, float b)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
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

void DrawingManager::DrawStaticEntity(Entity* entity)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(entity->x, entity->y, 0.0f);
	Vertex2D quadData[4] = {
			{ -entity->width / 2.0f, entity->height / 2.0f, 0.0f, 0.0f, 1.0f },
			{ -entity->width / 2.0f, -entity->height / 2.0f, 0.0f, 0.0f, 1.0f },
			{ entity->width / 2.0f, -entity->height / 2.0f, 0.0f, 0.0f, 1.0f },
			{ entity->width / 2.0f, entity->height / 2.0f, 0.0f, 0.0f, 1.0f }
	};
	glVertexPointer(2, GL_FLOAT, sizeof(float) * 5, quadData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &quadData[0].r);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
}

void DrawingManager::DrawPrize(Entity* entity)
{
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(entity->x, entity->y, 0.0f);
	Vertex2D quadData[4] = {
			{ -entity->width / 2.0f, entity->height / 2.0f, 0.0f, 1.0f, 0.5f },
			{ -entity->width / 2.0f, -entity->height / 2.0f, 0.0f, 1.0f, 0.5f },
			{ entity->width / 2.0f, -entity->height / 2.0f, 0.0f, 1.0f, 0.5f },
			{ entity->width / 2.0f, entity->height / 2.0f, 0.0f, 1.0f, 0.5f }
	};
	glVertexPointer(2, GL_FLOAT, sizeof(float) * 5, quadData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &quadData[0].r);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
	glPopMatrix();
}

void DrawingManager::DrawLavaBlob(Entity* entity)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(entity->x, entity->y, 0.0f);
	Vertex2D quadData[4] = {
			{ -entity->width / 2.0f, entity->height / 2.0f, 1.0f, rand() % 100 * .01f, 0.5f },
			{ -entity->width / 2.0f, -entity->height / 2.0f, 1.0f, rand() % 100 * .01f, 0.5f },
			{ entity->width / 2.0f, -entity->height / 2.0f, 1.0f, rand() % 100 * .01f, 0.5f },
			{ entity->width / 2.0f, entity->height / 2.0f, 1.0f, rand() % 100 * .01f, 0.5f }
	};
	glVertexPointer(2, GL_FLOAT, sizeof(float) * 5, quadData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &quadData[0].r);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
}

void DrawingManager::DrawRocketBoost(float x, float y)
{
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(x - (.08f + rand() % 10 * .01f), y - (.08f + rand() % 10 * .01f), 0.0f);
	Vertex2D quadData[4] = {
			{ -.05f, .05f, 1.0f, rand() % 100 * .01f, 0.5f },
			{ -.05f, -.05f, 1.0f, rand() % 100 * .01f, 0.5f },
			{ .05f, -.05f, 1.0f, rand() % 100 * .01f, 0.5f },
			{ .05f, .05f, 1.0f, rand() % 100 * .01f, 0.5f }
	};
	glVertexPointer(2, GL_FLOAT, sizeof(float) * 5, quadData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &quadData[0].r);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
	glPopMatrix();
}

void DrawingManager::DrawSprite(GLuint texture, float x, float y, float width, float height, float rotation)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0);
	//glRotatef(rotation, 0.0, 0.0, 1.0);
	GLfloat quad[] = { -width / 2.0f, height / 2.0f, -width / 2.0f, -height / 2.0f, width / 2.0f, -height / 2.0f, width / 2.0f, height / 2.0f };
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

void DrawingManager::DrawSomeText(std::string text, float x, float y, float size, float spacing, float r, float g, float b, float a)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, fontTexture);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(x, y, 0.0f);

	float texture_size = 1.0 / 16.0f;

	std::vector<float> vertexData;
	std::vector<float> texCoordData;
	std::vector<float> colorData;

	for (int i = 0; i < text.size(); i++) {
		float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
		float texture_y = (float)(((int)text[i]) / 16) / 16.0f;
		vertexData.insert(vertexData.end(), {
			((size + spacing) * i) + (-0.5f * size), 0.5f * size,
			((size + spacing) * i) + (-0.5f * size), -0.5f * size,
			((size + spacing) * i) + (0.5f * size), -0.5f * size,
			((size + spacing) * i) + (0.5f * size), 0.5f * size
		});
		colorData.insert(colorData.end(), { r, g, b, a, r, g, b, a, r, g, b, a, r, g, b, a });
		texCoordData.insert(texCoordData.end(), { texture_x, texture_y, texture_x, texture_y + texture_size, texture_x +
			texture_size, texture_y + texture_size, texture_x + texture_size, texture_y });
	}

	glColorPointer(4, GL_FLOAT, 0, colorData.data());
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
	glEnableClientState(GL_VERTEX_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_QUADS, 0, text.size() * 4);
	
	
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glPopMatrix();

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

void DrawingManager::DrawSheetSpriteNonUniform(Entity* entity)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteSheetTexture);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(entity->x, entity->y, 0.0);
	//glRotatef(rotation, 0.0, 0.0, 1.0);
	GLfloat quad[] = { -(entity->width) /*/ 2.0f*/, entity->height /*/ 2.0f*/, -(entity->width) /*/ 2.0f*/, -(entity->height) /*/ 2.0f*/, entity->width /*/ 2.0f*/, -(entity->height) /*/ 2.0f*/, entity->width /*/ 2.0f*/, entity->height /*/ 2.0f*/ };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat quadUVs[] = { entity->u, entity->v, entity->u, entity->v + entity->height, entity->u + entity->width, entity->v + entity->height, entity->u + entity->width, entity->v };

	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_QUADS, 0, 4);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void DrawingManager::DrawSheetSpriteUniform(Entity* entity, int index)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteSheetTexture);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(entity->x, entity->y, 0.0);
	//glRotatef(rotation, 0.0, 0.0, 1.0);
	GLfloat quad[] = { -(entity->width), entity->height, -(entity->width), -(entity->height), entity->width, -(entity->height), entity->width, entity->height };
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
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void DrawingManager::DrawStatBoard(int energy, int score)
{
	DrawSomeText("Score: " + std::to_string(score), -2.63f, 1.96f, 0.15f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("Energy: " + std::to_string(energy), 1.1f, 1.96f, 0.15f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}

void DrawingManager::DrawStartScreen()
{
	DrawSomeText("SAM WEISSMAN", -1.0f, 1.2f, 0.15f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("PRESENTS", -0.8f, 1.1f, 0.15f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("ROCKET RUNNER", -1.0f, 1.0f, 0.15f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	DrawSomeText("PRESS UP ARROW", -1.1f, .9f, 0.15f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	DrawSomeText("TO PLAY", -0.7f, .8f, 0.15f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("SPACEBAR: FLY", -2.64f, -1.95f, 0.15f, -0.02f, 0.0f, 1.0f, 0.0f, 1.0f);
	DrawSomeText("DOWN ARROW: CROUCH", 0.2f, -1.95f, 0.15f, -0.02f, 0.0f, 1.0f, 0.0f, 1.0f);
	DrawSomeText("Flying uses energy until it reaches 0.", -1.3f, -.6f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, 1.0f);
	DrawSomeText("After energy runs out, jetpack stops.", -1.4f, -.75f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, 1.0f);
	DrawSomeText("Land for faster energy recharge.", -1.2f, -.9f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, 1.0f);
	DrawSomeText("Collect greens for score and a possible boost!", -2.0f, -1.05f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, 1.0f);
}
void DrawingManager::DrawYouLose(int score, float xZone)
{
	DrawSomeText("FINAL SCORE", -1.0f + xZone, 0.9f, 0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText(std::to_string(score), -0.2f + xZone, 0.8f, 0.2f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	DrawSomeText("YOU LOSE", -0.9f + xZone, 0.1f, 0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("TO TRY AGAIN", -1.1f + xZone, 0.0f, 0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("PRESS UP ARROW", -1.2f + xZone, -0.1f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
}
/*void DrawingManager::DrawYouWin(int score)
{
	DrawSomeText("FINAL SCORE", -0.5f, 0.9f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText(std::to_string(score), -0.1f, 0.8f, 0.1f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	DrawSomeText("YOU WIN", -0.4f, 0.1f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("TO PLAY AGAIN", -0.6f, 0.0f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("PRESS SPACEBAR", -0.7f, -0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
}*/

void DrawingManager::DrawTileLevel(unsigned char levelData[LEVEL_HEIGHT][LEVEL_WIDTH], float zone)
{
	glBindTexture(GL_TEXTURE_2D, spriteSheetTexture);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	int numOfVertices = 0;

	std::vector<float> vertexData;
	std::vector<float> texCoordData;
	std::vector<float> colorData;

	for (int y = 0; y < LEVEL_HEIGHT; y++)
	{
		for (int x = 0; x < LEVEL_WIDTH; x++)
		{
			if (levelData[y][x] > 0)
			{
				float u = (float)(((int)levelData[y][x]) % SPRITE_COUNT_X) / (float)SPRITE_COUNT_X;
				float v = (float)(((int)levelData[y][x]) / SPRITE_COUNT_X) / (float)SPRITE_COUNT_Y;
				float spriteWidth = 1.0f / (float)SPRITE_COUNT_X;
				float spriteHeight = 1.0f / (float)SPRITE_COUNT_Y;

				vertexData.insert(vertexData.end(), {
					TILE_SIZE * x, -TILE_SIZE * y,
					TILE_SIZE * x, (-TILE_SIZE * y) - TILE_SIZE,
					(TILE_SIZE * x) + TILE_SIZE, (-TILE_SIZE * y) - TILE_SIZE,
					(TILE_SIZE * x) + TILE_SIZE, -TILE_SIZE * y
				});
				texCoordData.insert(texCoordData.end(), { u, v,
					u, v + (spriteHeight),
					u + spriteWidth, v + (spriteHeight),
					u + spriteWidth, v
				});

				numOfVertices += 4;
			}
		}
	}

	glTranslatef((-TILE_SIZE * LEVEL_WIDTH / 2) + zone, TILE_SIZE * LEVEL_HEIGHT/2, 0.0f );
	glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
	glEnableClientState(GL_VERTEX_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_QUADS, 0, numOfVertices);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}
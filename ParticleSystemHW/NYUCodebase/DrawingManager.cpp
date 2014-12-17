#pragma once
#include <stdlib.h>
#include <vector>
#include <string>
#include "DrawingManager.h"
#include "Entity.h"

DrawingManager::DrawingManager()
{
	fontTexture = LoadTexture("font1.png");
	spriteSheetTexture = LoadTexture("sheet.png");
	alienFace = LoadTexture("samspaceinvaderlaugh3a.png");
	deathSpreeFace = LoadTexture("samspaceinvaderlaugh3c.png");
	alienHostage = LoadTexture("samspaceinvaderhostage.png");
	rotation = 0.0f;
	screenShakeValue = 0.0f;
	screenShakeSpeed = 0.0f;
	screenShakeIntensity = 0.0f;
	startScreenReady = false;
	samWeissmanDone = false;
	presentsDone = false;
	spaceInvadersDone = false;
	showControlsDone = false;
	textTimer = 1.0f;
}
DrawingManager::~DrawingManager()
{

}

void DrawingManager::DrawAlienFace(int textureNum)
{
	GLuint texture;
	switch (textureNum)
	{
	case 0:
		texture = alienFace;
		break;
	case 1:
		texture = deathSpreeFace;
		break;
	case 2:
		texture = alienHostage;
		break;
	default:
		break;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f + ((sin(screenShakeValue * screenShakeSpeed) / 100.0f) * screenShakeIntensity), 0.0f, 0.0);
	//glRotatef(rotation, 0.0, 0.0, 1.0);
	GLfloat quad[] = { -1.5f, 1.0f, -1.5f, -1.0f, 1.5f, -1.0f, 1.5f, 1.0f};
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
void DrawingManager::DrawBoost(float x, float y)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x + (-.04f + rand() % 8 * .01f) + ((sin(screenShakeValue * screenShakeSpeed) / 100.0f) * screenShakeIntensity), y - (.06f + rand() % 8 * .01f), 0.0f);
	Vertex2D quadData[4] = {
			{ -.025f, .025f, 1.0f, rand() % 100 * .01f, 0.5f, 1.0f },
			{ -.025f, -.025f, 1.0f, rand() % 100 * .01f, 0.5f, 1.0f },
			{ .025f, -.025f, 1.0f, rand() % 100 * .01f, 0.5f, 1.0f },
			{ .025f, .025f, 1.0f, rand() % 100 * .01f, 0.5f, 1.0f }
	};
	glVertexPointer(2, GL_FLOAT, sizeof(float) * 6, quadData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_FLOAT, sizeof(float) * 6, &quadData[0].r);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
}

void DrawingManager::shakeScreen(float elapsed, float shakeSpeed, float shakeIntensity)
{
	screenShakeValue += elapsed;
	screenShakeSpeed = shakeSpeed;
	screenShakeIntensity = shakeIntensity;
}

void DrawingManager::stopScreenShake()
{
	screenShakeSpeed, screenShakeIntensity = 0.0f;
}

void DrawingManager::DrawBullet(Bullet* bullet, bool isEnemy)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(bullet->getX() + ((sin(screenShakeValue * screenShakeSpeed) / 100.0f) * screenShakeIntensity), bullet->getY(), 0.0f);
	glRotated(bullet->getAngle(), 0.0f, 0.0f, 1.0f);
	float r, g, b;
	if (!isEnemy)
	{
		r = 1.0f;
		g = 1.0f;
		b = 0.0f;
	}
	else
	{
		r = 1.0f;
		g = 0.0f;
		b = 1.0f;
	}
	Vertex2D quadData[4] =	{	
								{ -bullet->getSize(), bullet->getSize(), r, g, b, 1.0f }, 
								{ -bullet->getSize(), -bullet->getSize(), r, g, b, 1.0f }, 
								{ bullet->getSize(), -bullet->getSize(), r, g, b, 1.0f }, 
								{ bullet->getSize(), bullet->getSize(), r, g, b, 1.0f }
							};
	glVertexPointer(4, GL_FLOAT, sizeof(float) * 6, quadData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_FLOAT, sizeof(float) * 6, &quadData[0].r);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
}

void DrawingManager::DrawStar(Star star)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPointSize(rand() % 2);
	std::vector<float> starVertices;
	std::vector<float> colorVertices;
	starVertices.push_back(star.x);
	starVertices.push_back(star.y);
	if (rand() % 10 > 5)
	{
		colorVertices.push_back(1.0f);
		colorVertices.push_back(1.0f);
		colorVertices.push_back(1.0f);
		colorVertices.push_back(1.0f);
	}
	else
	{
		colorVertices.push_back(0.0f);
		colorVertices.push_back(0.0f);
		colorVertices.push_back(1.0f);
		colorVertices.push_back(1.0f);
	}
	glVertexPointer(2, GL_FLOAT, 0, starVertices.data());
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, colorVertices.data());
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_POINTS, 0, starVertices.size() / 2);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
}

void DrawingManager::DrawBulletTrail(Bullet* bullet, bool isEnemy)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLineWidth(4.0f);
	glTranslatef(bullet->getX() + ((sin(screenShakeValue * screenShakeSpeed) / 100.0f) * screenShakeIntensity), bullet->getY(), 0.0f);
	float r, g, b, firstA, lastA, start, end;
	if (!isEnemy)
	{
		r = 1.0f;
		g = 1.0f;
		b = 0.0f;
		firstA = 1.0f;
		lastA = 0.0f;
		start = bullet->getSize() / 2.0f;
		end = -bullet->getSize() * 30.0f;
	}
	else
	{
		r = 1.0f;
		g = 0.0f;
		b = 1.0f;
		firstA = 1.0f;
		lastA = 0.0f;
		start = bullet->getSize() / 2.0f;
		end = bullet->getSize() * 15.0f;
	}
	Vertex2D lineData[2] = {
			{ 0.0f, start, r, g, b, firstA },
			{ 0.0f, end, r, g, b, lastA },
	};
	glVertexPointer(2, GL_FLOAT, sizeof(float) * 6, lineData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_FLOAT, sizeof(float) * 6, &lineData[0].r);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_LINES, 0, 2);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
}

void DrawingManager::DrawEnemyEngineTrail(Entity* enemy)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLineWidth(4.0f);
	glTranslatef(enemy->getX() + ((sin(screenShakeValue * screenShakeSpeed) / 100.0f) * screenShakeIntensity), enemy->getY(), 0.0f);
	Vertex2D lineData[2] = {
			{ 0.0f, enemy->getHeight() * (6.0f - rand() % 3), 1.0f, .5f, 0.0f, 0.0f },
			{ 0.0f, enemy->getHeight() / 2.0f - .025f, 1.0f, .5f, 0.0f, 1.0f },
	};
	glVertexPointer(2, GL_FLOAT, sizeof(float) * 6, lineData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_FLOAT, sizeof(float) * 6, &lineData[0].r);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_LINES, 0, 2);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
}

void DrawingManager::DrawSprite(GLuint texture, float x, float y, float width, float height, float rotation)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x + ((sin(screenShakeValue * screenShakeSpeed) / 100.0f) * screenShakeIntensity), y, 0.0);
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
	glLoadIdentity();
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

void DrawingManager::DrawSheetSprite(Entity* entity)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteSheetTexture);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(entity->getX() + ((sin(screenShakeValue * screenShakeSpeed) / 100.0f) * screenShakeIntensity), entity->getY(), 0.0);
	GLfloat quad[] = { -(entity->getWidth()) / 2.0f, entity->getHeight() / 2.0f, -(entity->getWidth()) / 2.0f, -(entity->getHeight()) / 2.0f, entity->getWidth() / 2.0f, -(entity->getHeight()) / 2.0f, entity->getWidth() / 2.0f, entity->getHeight() / 2.0f };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat quadUVs[] = { entity->getU(), entity->getV(), entity->getU(), entity->getV() + entity->getHeight(), entity->getU() + entity->getWidth(), entity->getV() + entity->getHeight(), entity->getU() + entity->getWidth(), entity->getV() };

	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
}

void DrawingManager::DrawWarp(float warpX, float elapsed)
{
	rotation += 1440.0f * elapsed;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteSheetTexture);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(warpX + ((sin(screenShakeValue * screenShakeSpeed) / 100.0f) * screenShakeIntensity), -0.9f, 0.0);
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);
	GLfloat quad[] = { -36.0f / 1024.0f, 36.0f / 1024.0f, -36.0f / 1024.0f, -36.0f / 1024.0f, 36.0f / 1024.0f, -36.0f / 1024.0f, 36.0f / 1024.0f, 36.0f / 1024.0f };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat quadUVs[] = { 699.0f / 1024.0f, 795.0f / 1024.0f, 699.0f / 1024.0f, 795.0f / 1024.0f + 36.0f / 1024.0f, 699.0f / 1024.0f + 36.0f / 1024.0f, 795.0f / 1024.0f + 36.0f / 1024.0f, 699.0f / 1024.0f + 36.0f / 1024.0f, 795.0f / 1024.0f };

	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
}

void DrawingManager::DrawStatBoard(int health, int wave, int score)
{
	DrawSomeText("Health:" + std::to_string(health), -1.3f, .97f, 0.075f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("Wave:" + std::to_string(wave), -0.15, .97f, 0.075f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("Score:" + std::to_string(score), 0.65f, .97f, 0.075f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}

void DrawingManager::DrawStartScreen()
{
	DrawSomeText("SAM WEISSMAN", -0.5f, 0.2f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("PRESENTS", -0.4f, 0.1f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("SPACE INVADERS", -0.6f, 0.0f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("PRESS SPACEBAR", -0.6f, -0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	DrawSomeText("TO PLAY", -0.3f, -0.2f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("Z: SET WARP", -1.3f, -.75f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, 1.0f);
	DrawSomeText("X: GO TO WARP", 0.35f, -.75f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, 1.0f);
	DrawSomeText("CTRL: SHOOT", -1.3f, -.95f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, 1.0f);
	DrawSomeText("SHIFT: BOOST", 0.4f, -.95f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, 1.0f);
}

void DrawingManager::SamWeissman()
{
	if (textTimer > 0.2f)
	{
		textTimer -= .02f;
		DrawSomeText("SAM WEISSMAN", -0.5f, textTimer, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		samWeissmanDone = false;
	}
	else
	{
		textTimer = 1.0f;
		DrawSomeText("SAM WEISSMAN", -0.5f, 0.2f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		samWeissmanDone = true;
	}
}

void DrawingManager::Presents()
{
	DrawSomeText("SAM WEISSMAN", -0.5f, 0.2f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	if (textTimer > .1f)
	{
		textTimer -= .02f;
		DrawSomeText("PRESENTS", -0.4f, textTimer, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		presentsDone = false;
	}
	else
	{
		textTimer = 1.0f;
		DrawSomeText("PRESENTS", -0.4f, 0.1f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		presentsDone = true;
	}
}

void DrawingManager::SpaceInvaders()
{
	DrawSomeText("SAM WEISSMAN", -0.5f, 0.2f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("PRESENTS", -0.4f, 0.1f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	if (textTimer > 0.0f)
	{
		textTimer -= .02f;
		DrawSomeText("SPACE", -0.6f - textTimer, 0.0f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		DrawSomeText("INVADERS", -0.0f + textTimer, 0.0f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		spaceInvadersDone = false;
	}
	else
	{
		textTimer = 0.0f;
		DrawSomeText("SPACE", -0.6f, 0.0f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		DrawSomeText("INVADERS", 0.0f, 0.0f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		spaceInvadersDone = true;
	}
}
void DrawingManager::ShowControls()
{
	DrawSomeText("SAM WEISSMAN", -0.5f, 0.2f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("PRESENTS", -0.4f, 0.1f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("SPACE", -0.6f, 0.0f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("INVADERS", 0.0f, 0.0f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	if (textTimer < 1.0f)
	{
		textTimer += .02f;
		DrawSomeText("PRESS SPACEBAR", -0.6f, -0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f, textTimer);
		DrawSomeText("TO PLAY", -0.3f, -0.2f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, textTimer);
		DrawSomeText("Z: SET WARP", -1.3f, -.75f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, textTimer);
		DrawSomeText("X: GO TO WARP", 0.35f, -.75f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, textTimer);
		DrawSomeText("CTRL: SHOOT", -1.3f, -.95f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, textTimer);
		DrawSomeText("SHIFT: BOOST", 0.4f, -.95f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, textTimer);
		showControlsDone = false;
	}
	else
	{
		DrawSomeText("PRESS SPACEBAR", -0.6f, -0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		DrawSomeText("TO PLAY", -0.3f, -0.2f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		DrawSomeText("Z: SET WARP", -1.3f, -.75f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, textTimer);
		DrawSomeText("X: GO TO WARP", 0.35f, -.75f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, textTimer);
		DrawSomeText("CTRL: SHOOT", -1.3f, -.95f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, 1.0f);
		DrawSomeText("SHIFT: BOOST", 0.4f, -.95f, 0.1f, -0.02f, 1.0f, 1.0f, 0.0f, 1.0f);
		showControlsDone = true;
		startScreenReady = true;
	}
}
void DrawingManager::DrawYouLose(int score)
{
	DrawSomeText("FINAL SCORE", -0.5f, 0.9f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText(std::to_string(score), -0.1f, 0.8f, 0.1f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	DrawSomeText("YOU LOSE", -0.4f, 0.1f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("TO TRY AGAIN", -0.6f, 0.0f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("PRESS SPACEBAR", -0.7f, -0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
}
void DrawingManager::DrawYouWin(int score)
{
	DrawSomeText("FINAL SCORE", -0.5f, 0.9f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText(std::to_string(score), -0.1f, 0.8f, 0.1f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	DrawSomeText("YOU WIN", -0.4f, 0.1f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("TO PLAY AGAIN", -0.6f, 0.0f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSomeText("PRESS SPACEBAR", -0.7f, -0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
}

bool DrawingManager::getSWComplete()
{
	return samWeissmanDone;
}

bool DrawingManager::getPresentsComplete()
{
	return presentsDone;
}

bool DrawingManager::getSpaceInvadersComplete()
{
	return spaceInvadersDone;
}

bool DrawingManager::getShowControlsComplete()
{
	return showControlsDone;
}

bool DrawingManager::getStartScreenReady()
{
	return startScreenReady;
}
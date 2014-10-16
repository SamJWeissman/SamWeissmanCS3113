#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <stdlib.h>
#include "GameManager.h"
#include "Entity.h"
#include <vector>

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6

enum GAMESTATE { STATE_START_SCREEN, STATE_GAME_RUNNING, STATE_GAME_LOSE };

GameManager::GameManager(){}

GameManager::~GameManager(){}

void GameManager::init()
{
	setupGL();
	setupGameVariables();
}

void GameManager::setupGL()
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-2.66, 2.66, -2.0, 2.0, -1.0, 1.0);
}

void GameManager::setupGameVariables()
{
	gameOver = false;
	lastFrameTicks = 0.0f;
	elapsed = 0.0f;
	timeLeftOver = 0.0f;
	player = new Player();
	unsigned char level1Data[LEVEL_HEIGHT][LEVEL_WIDTH] = {};
	unsigned int runAnimationData[5] = {66, 67, 68, 69, 70};
	for (int i = 13; i < 16; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			level1Data[i][j] = 4;
		}
	}

	memcpy(levelData, level1Data, LEVEL_HEIGHT * LEVEL_WIDTH);
	memcpy(runAnimation, runAnimationData, 25);

	drawingMgr = new DrawingManager();
	xZone = 0.0f;
	entities.push_back(player->playerEntLegs);
	previousX = -2.66f;
	entities.push_back(player->playerEntTorso);
	player->playerEntTorso->index = 99;
	numFrames = 5;
	currentIndex = 0;
	animationElapsed = 0.0f;
	framesPerSecond = 30.0f;
	srand(SDL_GetTicks());

}

void GameManager::fixedUpdate()
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->FixedUpdate();
		entities[i]->moveY();
		//handleYPenetration(entities[i], entities);
		checkYlevelCollision(entities[0]);
		entities[i]->moveX();
		checkXlevelCollision(entities[0]);
		//handleXPenetration(entities[i], entities);
	}
}

void GameManager::fixedLoop()
{
	ticks = (float)SDL_GetTicks() / 1000.0f;
	elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;
	timer += elapsed;

	float fixedElapsed = elapsed + timeLeftOver;
	if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS) {
		fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
	}

	while (fixedElapsed >= FIXED_TIMESTEP) {
		fixedElapsed -= FIXED_TIMESTEP;
		fixedUpdate();
	}
	timeLeftOver = fixedElapsed;
}

void GameManager::update(float elapsed)
{
	player->Update(elapsed);
	if (fabs(player->playerEntLegs->x - previousX) > 6.65f)
	{
		xZone += 6.65f;
		obstacleVal = rand() % 1000; 
		previousX = player->playerEntLegs->x;
	}
	obstacle(obstacleVal); //this adds tiles which are detected by collision but are not rendered properly. I spent hours trying to figure out why and could not solve.
	animationElapsed += elapsed;
}

void GameManager::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawingMgr->DrawStatBoard(player->energy, player->score);
	glTranslatef(-entities[0]->x, 0.0f, 0.0f);
	drawingMgr->DrawTileLevel(levelData, xZone);
	drawingMgr->DrawSheetSpriteUniform(player->playerEntTorso, player->playerEntTorso->index);
	if (player->playerEntLegs->y < -1.0f){
		if (animationElapsed > 1.0 / 30.0f) {
			currentIndex++;
			animationElapsed = 0.0;
			if (currentIndex > numFrames - 1) {
				currentIndex = 0;
			}
		}
		drawingMgr->DrawSheetSpriteUniform(player->playerEntLegs, runAnimation[currentIndex]);
	}
	else
	{
		drawingMgr->DrawSheetSpriteUniform(player->playerEntLegs, runAnimation[2]);
	}

	player->resetPlayerEnts();
	SDL_GL_SwapWindow(displayWindow);
}

void GameManager::updateAndRender()
{
	fixedLoop();
	update(elapsed);
	render();
}

void GameManager::processEvents(SDL_Event &event)
{

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
		{
			gameOver = true;
		}
	}
	player->checkInputControls();
}

void GameManager::handleYPenetration(Entity* entity, std::vector<Entity*> entities)
{
	if (!entity->isStatic && entity->enableCollisions)
	{
		for (int i = 0; i < entities.size(); i++) {
			if (entities[i] != entity && entities[i]->isStatic)
			{
				if (entity->collidesWith(entities[i]))
				{
					if (entity->y < entities[i]->y)
					{
						entity->y += fabs(entity->y - entities[i]->y) -
							(entity->height * 0.5f) - (entities[i]->height * 0.5f) - .001f;
						entity->collidedTop = true;
					}
					else
					{
						entity->collidedBottom = true;
						entity->y -= fabs(entity->y - entities[i]->y) -
							(entity->height * 0.5f) - (entities[i]->height * 0.5f) - .001f;
					}
					entity->velocity_y = 0.0f;
				}
			}
		}
	}
}

void GameManager::handleXPenetration(Entity* entity, std::vector<Entity*> entities)
{
	if (!entity->isStatic && entity->enableCollisions)
	{
		for (int i = 0; i < entities.size(); i++) {
			if (entities[i] != entity && entities[i]->isStatic && !entity->collidedBottom)
			{
				if (entity->collidesWith(entities[i]))
				{
					if (entity->x < entities[i]->x)
					{
						entity->x += fabs(entity->x - entities[i]->x) -
							(entity->width * 0.5f) - (entities[i]->width * 0.5f) - .001f;
						entity->collidedRight = true;
					}
					else
					{
						entity->collidedLeft = true;
						entity->x -= fabs(entity->x - entities[i]->x) -
							(entity->width * 0.5f) - (entities[i]->width * 0.5f) - .001f;
					}
					entity->velocity_x = 0.0f;
				}
			}
		}
	}
}

bool GameManager::isGameOver()
{
	return gameOver;
}

bool GameManager::isSolid(unsigned char tile)
{
	switch (tile)
	{
	case 4:
		return true;
		break;
	default:
		return false;
		break;
	}
}

void GameManager::worldToTileCoordinates(float worldX, float worldY, int *gridX, int *gridY)
{
	*gridX = (int)(((worldX) / (TILE_SIZE) + 32.0));
	*gridY = (int)((-worldY / (TILE_SIZE) + 8.0));
}

float GameManager::pointAndGridCollisionXaxis(float x, float y)
{
	int xGrid, yGrid;
	worldToTileCoordinates(x, y, &xGrid, &yGrid);

	if (isSolid(levelData[yGrid][xGrid]))
	{
		float xAdjust = ((xGrid + 1) * TILE_SIZE) - (TILE_SIZE * 32.0);
		return xAdjust - x;
	}
	return 0.0f;
}

float GameManager::pointAndGridCollisionYaxis(float x, float y)
{
	int xGrid, yGrid;
	worldToTileCoordinates(x, y, &xGrid, &yGrid);

	if (isSolid(levelData[yGrid][xGrid]))
	{
		float yAdjust = (yGrid * TILE_SIZE) - (TILE_SIZE * 8.0);
		return -y - yAdjust;
	}
	return 0.0f;
}

void GameManager::checkXlevelCollision(Entity* entity)
{
	float xPenetration = pointAndGridCollisionXaxis(entity->x - xZone - entity->width, entity->y);
	if (xPenetration != 0.0f)
	{
		entity->x += xPenetration;
		entity->velocity_x = 0.0f;
		entity->collidedLeft = true;
	}

	xPenetration = pointAndGridCollisionXaxis(entity->x - xZone + (entity->width / 2.0f), entity->y);
	if (xPenetration != 0.0f)
	{
		entity->x += xPenetration - (TILE_SIZE);
		entity->velocity_x = 0.0f;
		entity->collidedRight = true;
		//gameOver = true; WILL ADD THIS IN ONCE I CAN ACTUALLY SEE THE TILES BEING RENDERED
	}
}

void GameManager::checkYlevelCollision(Entity* entity)
{
	float yPenetration = pointAndGridCollisionYaxis(entity->x - xZone, entity->y - entity->height);
	if (yPenetration != 0.0f)
	{
		entity->y += yPenetration;
		entity->velocity_y = 0.0f;
		entity->collidedBottom = true;
	}

	yPenetration = pointAndGridCollisionYaxis(entity->x - xZone, entity->y + (entity->height / 2.0f));
	if (yPenetration != 0.0f)
	{
		entity->y += yPenetration - (TILE_SIZE);
		entity->velocity_y = 0.0f;
		entity->collidedTop = true;
	}
}

void GameManager::obstacle(int x)
{
	if (0 <= x && x < 200 )
	{
		levelData[12][32] = 4;
		levelData[11][32] = 0;
		levelData[10][32] = 0;
	}
	else if (200 <= x && x < 400)
	{
		levelData[12][32] = 4;
		levelData[11][32] = 4;
		levelData[10][32] = 0;
	}
	else if(400 <= x && x < 600)
	{
		levelData[12][32] = 4;
		levelData[11][32] = 4;
		levelData[10][32] = 4;
	}
	else if (600 <= x && x < 800)
	{
		levelData[12][32] = 4;
		levelData[11][32] = 4;
		levelData[10][32] = 0;
		levelData[9][32] = 0;
		levelData[8][32] = 4;
		levelData[7][32] = 4;
	}
	else if (800 <= x && x < 1000)
	{
		levelData[12][32] = 4;
		levelData[11][32] = 0;
		levelData[10][32] = 0;
		levelData[9][32] = 4;
		levelData[8][32] = 0;
		levelData[7][32] = 0;
		levelData[6][32] = 4;
	}
}

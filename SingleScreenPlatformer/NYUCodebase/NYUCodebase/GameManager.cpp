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
	state = STATE_START_SCREEN;
	player = new Player();
	drawingMgr = new DrawingManager();
	entityMgr = new EntityManager();
	entities.push_back(player->playerEnt);
	entities.push_back(new Entity(0.0f, -1.0f, 0.0f, 0.0f, .8f, 0.2f, 0.0f, 0.0f, true));
}

void GameManager::fixedUpdate()
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->FixedUpdate();
		entities[i]->moveY();
		handleYPenetration(entities[i], entities);
		entities[i]->moveX();
		handleXPenetration(entities[i], entities);
	}
	for (int i = 0; i < entityMgr->lavaBlobs.size(); i++)
	{
		entityMgr->lavaBlobs[i]->FixedUpdate();
		entityMgr->lavaBlobs[i]->moveY();
		entityMgr->lavaBlobs[i]->moveX();
	}
}

void GameManager::fixedLoop()
{
	ticks = (float)SDL_GetTicks() / 1000.0f;
	elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

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
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->resetCollisionBools();
	}
}

void GameManager::render()
{
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 152; i++)
	{
		drawingMgr->DrawQuad(.175f, .8 + rand() % 30 * .01f, -2.5725f + (i * .175f), -2.0f, 1.0f, rand() % 100 * .01f, 0.1f);
	}
	if (entities.size() > 1)
	{
		drawingMgr->DrawStaticEntity(entities[1]);
	}
	if (prizes.size() > 0)
	{
		for (int i = 0; i < prizes.size(); i++)
		{
			drawingMgr->DrawPrize(prizes[i]);
		}
	}
	if (entityMgr->lavaBlobs.size() > 0)
	{
		for (int i = 0; i < entityMgr->lavaBlobs.size(); i++)
		{
			drawingMgr->DrawLavaBlob(entityMgr->lavaBlobs[i]);
		}
	}
	drawingMgr->DrawSheetSprite(player->playerEnt);
	drawingMgr->DrawStatBoard(player->health, player->energy, player->score);
	
	if (player->energy > 0 && player->energy < 200 )
	{
		drawingMgr->DrawSomeText("LOW ENERGY", -2.3f, 1.5f, .5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	}
	else if (player->energy <= 0)
	{
		drawingMgr->DrawSomeText("NO ENERGY", -2.2f, 1.5f, .5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	}

	SDL_GL_SwapWindow(displayWindow);
}

void GameManager::renderGameLost()
{
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	drawingMgr->DrawYouLose(player->score);

	SDL_GL_SwapWindow(displayWindow);
}

void GameManager::renderStartScreen()
{
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	drawingMgr->DrawStartScreen();

	SDL_GL_SwapWindow(displayWindow);
}

void GameManager::updateAndRender()
{
	fixedLoop();
	update(elapsed);
	if (state == STATE_GAME_RUNNING)
	{
		render();
	}
	else if(state == STATE_GAME_LOSE)
	{
		renderGameLost();
	}
	else
	{
		renderStartScreen();
	}
}

void GameManager::processEvents(SDL_Event &event)
{
	if (state == STATE_GAME_RUNNING)
	{
		player->collectPrize(prizes);
		entityMgr->lavaEruption();
		entityMgr->lavaBlobCollisions(player);
		if (prizes.size() <= 10)
		{
			entityMgr->spawnPrize(prizes);
		}

		if (entities.size() < 2)
		{
			entityMgr->createLanding(entities);
		}
		else
		{
			entityMgr->removeLanding(entities);
		}

		if (player->health <= 0 || player->playerEnt->y < -2.0f)
		{
			state = STATE_GAME_LOSE;
			player->health = 100;
			player->energy = 500;
			player->resetPlayerEnt();
		}
	}
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
		{
			gameOver = true;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_UP)
			{
				if (state == STATE_GAME_LOSE || state == STATE_START_SCREEN)
				{
					player->score = 0;
					player->resetPlayerEnt();
					state = STATE_GAME_RUNNING;
				}
			}
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
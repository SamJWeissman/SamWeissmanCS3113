#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "GameManager.h"
#include "DrawingManager.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Player.h"
#include "Bullet.h"
#include "CollisionManager.h"

enum GAMESTATE { STATE_START_SCREEN, STATE_GAME_RUNNING, STATE_GAME_LOSE, STATE_GAME_WIN };

GameManager::GameManager(){
	state = STATE_START_SCREEN;
}
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
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
}

void GameManager::setupGameVariables()
{
	gameOver = false;
	player = new Player();
	drawingManager = new DrawingManager();
	entityManager = new EntityManager(player);

	for (int i = 0; i < 30; i++)
	{
		enemyBullets.push_back(new Bullet(true));
	}
	enemyBulletCounter = 0;

	collisionManager = new CollisionManager(enemyBullets, entityManager, player);

	waveCounter = 0;
	screenShakeTime = 0.0f;

	lastFrameTicks = 0.0f;
	elapsed = 0.0f;
	timeLeftOver = 0.0f;

	entityManager->pushEntity(player->getSpaceship());
}

void GameManager::FixedUpdate()
{
	for (int i = 0; i < entityManager->numEntities(); i++)
	{
		entityManager->getEntityAt(i)->FixedUpdate();
		entityManager->getEntityAt(i)->moveY();
		//handleYPenetration(entities[i], entities);
		entityManager->getEntityAt(i)->moveX();
		//handleXPenetration(entities[i], entities);
	}
}

void GameManager::FixedLoop()
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
		FixedUpdate();
	}
	timeLeftOver = fixedElapsed;
}

void GameManager::adjustTime()
{
	ticks = (float)SDL_GetTicks() / 1000.0f;
	elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;
}

void GameManager::update()
{
	if (state == STATE_GAME_RUNNING)
	{
		for (int i = 0; i < player->getBullets().size(); i++)
		{
			enemyBullets[i]->update(elapsed);
			((player->getBullets())[i])->update(elapsed);
		}
	}
	entityManager->updateEmitters(elapsed);
	if (entityManager->enemyShipBrokeThrough())
	{
		screenShakeTime = 0.0f;
	}
	if (screenShakeTime < 1.0f)
	{
		drawingManager->shakeScreen(elapsed, 20.0f, 5.0f);
		screenShakeTime += elapsed;
	}
}

void GameManager::render()
{
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (state == STATE_GAME_RUNNING)
	{
		for (int i = 0; i < entityManager->numEntities(); i++)
		{
			drawingManager->DrawSheetSprite(entityManager->getEntityAt(i));
			if (i > 0)
			{
				drawingManager->DrawEnemyEngineTrail(entityManager->getEntityAt(i));
			}
			if (i > 0 && rand() % 1000 >= 997)
			{
				enemyBullets[i]->fire((entityManager->getEntityAt(i))->getX(), (entityManager->getEntityAt(i))->getY());
			}
			drawingManager->DrawBullet(enemyBullets[i]);
		}
		for (int i = 0; i < player->getBullets().size(); i++)
		{
			drawingManager->DrawBullet((player->getBullets())[i]);
			drawingManager->DrawBulletTrail((player->getBullets())[i]);
		}
		drawingManager->DrawStatBoard(player->getHealth(), player->getScore());
		entityManager->renderParticles();
		if (player->getBoost())
		{
			float x = player->getSpaceship()->getX();
			float y = player->getSpaceship()->getY();
			drawingManager->DrawBoost(x, y);
		}
	}
	else if (state == STATE_START_SCREEN)
	{
		drawingManager->DrawStartScreen();
	}
	else if (state == STATE_GAME_LOSE)
	{
		drawingManager->DrawYouLose(player->getScore());
	}
	else if (state == STATE_GAME_WIN)
	{
		drawingManager->DrawYouWin(player->getScore());
	}

	SDL_GL_SwapWindow(displayWindow);
}

void GameManager::updateAndRender()
{
	update();
	FixedLoop();
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
		else if (event.type == SDL_KEYDOWN)
		{
			if (state != STATE_GAME_RUNNING)
			{
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				{
					state = STATE_GAME_RUNNING;
					player->resetScore();
					entityManager->getEntityAt(0)->setX(0.0f);
					entityManager->firstWave();
					waveCounter++;
				}
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_LCTRL)
			{
				player->shoot();
				for (int i = 1; i < entityManager->numEntities(); i++)
				{
					Entity* ent = entityManager->getEntityAt(i);
					float diff = abs(player->getSpaceship()->getX() - ent->getX());
					if (diff < .1f && rand() % 1000 < 50)
					{
						if (ent->getX() < -0.0f)
						{
							ent->bankRight();
						}
						else
						{
							ent->bankLeft();
						}
					}
				}
			}
		}
	}

	if (entityManager->numEntities() < 15 && rand() % 1000 > 995)
	{
		entityManager->clusterWave();
	}
	if (entityManager->numEntities() < 2)
	{
		if (waveCounter == 1)
		{
			entityManager->secondWave();
			waveCounter++;
		}
		else if (waveCounter == 2)
		{
			entityManager->thirdWave();
			waveCounter++;
		}
		else if (waveCounter == 3 && player->getHealth() > 0)
		{
			state = STATE_GAME_WIN;
			waveCounter = 0;
			player->setHealth(100);
		}
	}

	player->checkInputControls();

	if (player->getHealth() <= 0)
	{
		state = STATE_GAME_LOSE;
		waveCounter = 0;
		player->setHealth(100);
	}

	collisionManager->bulletsVsEntities();
	if (collisionManager->bulletsVsPlayer())
	{
		screenShakeTime = 0.0f;
	}
	if (collisionManager->entityVsPlayer())
	{
		screenShakeTime = 0.0f;
	}
}

bool GameManager::isGameOver()
{
	return gameOver;
}
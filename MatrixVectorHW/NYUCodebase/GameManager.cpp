#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <stdlib.h>
#include "GameManager.h"
#include "Entity.h"
#include <vector>

enum GAMESTATE { STATE_START_SCREEN, STATE_GAME_RUNNING, STATE_GAME_LOSE };

GameManager::GameManager(){

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
	glOrtho(-2.66, 2.66, -2.0, 2.0, -1.0, 1.0);
}

void GameManager::setupGameVariables()
{
	//state = STATE_START_SCREEN;
	state = STATE_GAME_RUNNING;
	//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	//jetPack = Mix_LoadWAV("jet_pack.wav");
	//collectPrize = Mix_LoadWAV("prize.wav");
	gameOver = false;
	lastFrameTicks = 0.0f;
	elapsed = 0.0f;
	timeLeftOver = 0.0f;
	drawingMgr = new DrawingManager();

	player = new Player(drawingMgr);
	entities.push_back(player->ship);
	/*for (int i = 1; i < 3; i++)
	{
		entities.push_back(new Entity(drawingMgr));
	}*/
}

void GameManager::fixedUpdate()
{
	//player->ship->FixedUpdate();
	//player->ship->movePlayer();
	//handleXPenetration(player->ship, entities);
	//handleYPenetration(player->ship, entities);
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->FixedUpdate();
		entities[i]->movePlayer();
		//entities[i]->moveY();
		//handleYPenetration(entities[i], entities);
		//entities[i]->moveX();
		//handleXPenetration(entities[i], entities);
	}
}

void GameManager::fixedLoop()
{
	if (state == STATE_GAME_RUNNING)
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
}

void GameManager::update(float elapsed)
{
	if (state == STATE_GAME_RUNNING)
	{
		player->Update(elapsed);
		for (int i = 0; i < entities.size(); i++)
		{
			entities[i]->Update(elapsed);
		}
	}
}

void GameManager::render()
{
	glClearColor(0.0f, 0.05f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	entities[0]->renderShip();
	for (int i = 1; i < entities.size(); i++)
	{
		entities[i]->renderMeteor();
	}

	SDL_GL_SwapWindow(displayWindow);
}

void GameManager::renderGameLost()
{
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//drawingMgr->DrawYouLose(player->score, xZone);

	SDL_GL_SwapWindow(displayWindow);
}

void GameManager::renderStartScreen()
{
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//drawingMgr->DrawStartScreen();

	SDL_GL_SwapWindow(displayWindow);
}

void GameManager::updateAndRender()
{
	fixedLoop();
	update(elapsed);
	//if (state == STATE_GAME_RUNNING){
	render();
	//}
	/*else if (state == STATE_GAME_LOSE)
	{
		renderGameLost();
	}
	else
	{
		renderStartScreen();
	}*/
}

void GameManager::processEvents(SDL_Event &event)
{

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
		{
			gameOver = true;
			//Mix_FreeChunk(jetPack);
			//Mix_FreeChunk(collectPrize);
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_UP)
			{
				if (state == STATE_GAME_LOSE || state == STATE_START_SCREEN)
				{
					state = STATE_GAME_RUNNING;
					lastFrameTicks = (float)SDL_GetTicks() / 1000.0f;
				}
			}
		}
	}

	player->checkInputControls(elapsed);
}

void GameManager::handleYPenetration(Entity* entity, std::vector<Entity*> entities)
{

		for (int i = 0; i < entities.size(); i++) {
			if (entities[i] != entity)
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
					entity->velocity_y *= -1.0f;
					entity->acceleration_y *= -1.0f;
				}
			}
		}
}

void GameManager::handleXPenetration(Entity* entity, std::vector<Entity*> entities)
{

		for (int i = 0; i < entities.size(); i++) {
			if (entities[i] != entity && !entity->collidedBottom)
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
					entity->velocity_x *= -1.0f;
					entity->acceleration_x *= -1.0f;
				}
			}
		}
}

bool GameManager::isGameOver()
{
	return gameOver;
}

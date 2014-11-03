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
	state = STATE_GAME_RUNNING;
	gameOver = false;
	lastFrameTicks = 0.0f;
	elapsed = 0.0f;
	timeLeftOver = 0.0f;
	drawingMgr = new DrawingManager();

	player = new Player(drawingMgr);
	entities.push_back(player->ship);

	for (int i = 0; i < 10; i++)
	{
		entities.push_back(new Entity(drawingMgr));
	}
}

void GameManager::fixedUpdate()
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->FixedUpdate();
		entities[i]->moveY();
		//handleYPenetration(entities[i], entities);
		entities[i]->moveX();
		//handleXPenetration(entities[i], entities);
		if(checkForCollision(entities[0], entities[i]))
		{
			entities[0]->velocity_x = 0.0f;
			entities[0]->velocity_y = 0.0f; // **  CANNOT FOR THE LIFE OF ME FIGURE OUT  WHY THIS WONT WORK **
		};
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

bool GameManager::checkForCollision(Entity* e1, Entity* e2)
{
	e1->buildMatrix();
	e2->buildMatrix();

	//get corner point vectors
	Vector ent2topLeft = Vector(-e2->width * 0.5, e2->height * 0.5, 0.0);
	Vector ent2topRight = Vector(e2->width * 0.5, e2->height * 0.5, 0.0); 
	Vector ent2bottLeft = Vector(-e2->width * 0.5, -e2->height * 0.5, 0.0); 
	Vector ent2bottRight = Vector(e2->width * 0.5, -e2->height * 0.5, 0.0); 

	//convert to world space
	ent2topLeft = e2->matrix * ent2topLeft; 
	ent2topRight = e2->matrix * ent2topRight;
	ent2bottLeft = e2->matrix * ent2bottLeft;
	ent2bottRight = e2->matrix * ent2bottRight;

	//set corner point vectors in terms of obj space
	Matrix e1inv = e1->matrix.inverse();
	ent2topLeft = e1inv * ent2topLeft;
	ent2topRight = e1inv * ent2topRight;
	ent2bottLeft = e1inv * ent2bottLeft;
	ent2bottRight = e1inv * ent2bottRight;

	//get min x and max x
	float minX = fmin(fmin(fmin(ent2topLeft.x, ent2topRight.x), ent2bottLeft.x), ent2bottRight.x);
	float maxX = fmax(fmax(fmax(ent2topLeft.x, ent2topRight.x), ent2bottLeft.x), ent2bottRight.x);

	//check for x collision
	if (!(minX <= e1->width * 0.5 && maxX >= -e1->width * 0.5)) 
	{
		return false;
	}

	//get min y and max y
	float minY = fmin(fmin(fmin(ent2topLeft.y, ent2topRight.y), ent2bottLeft.y), ent2bottRight.y);
	float maxY = fmax(fmax(fmax(ent2topLeft.y, ent2topRight.y), ent2bottLeft.y), ent2bottRight.y);

	//check for y collision
	if (!(minY <= e1->height * 0.5 && maxY >= -e1->height * 0.5)) 
	{
		return false;
	}
	//get corner point vectors
	Vector ent1topLeft = Vector(-e1->width * 0.5, e1->height * 0.5, 0.0); 
	Vector ent1topRight = Vector(e1->width * 0.5, e1->height * 0.5, 0.0); 
	Vector ent1bottLeft = Vector(-e1->width * 0.5, -e1->height * 0.5, 0.0); 
	Vector ent1bottRight = Vector(e1->width * 0.5, -e1->height * 0.5, 0.0); 

	//convert to world space
	ent1topLeft = e1->matrix * ent1topLeft;
	ent1topRight = e1->matrix * ent1topRight;
	ent1bottLeft = e1->matrix * ent1bottLeft;
	ent1bottRight = e1->matrix * ent1bottRight;

	//set corner point vectors in terms of obj space
	Matrix e2inv = e2->matrix.inverse();
	ent1topLeft = e2inv * ent1topLeft;
	ent1topRight = e2inv * ent1topRight;
	ent1bottLeft = e2inv * ent1bottLeft;
	ent1bottRight = e2inv * ent1bottRight;

	//get min x and max x
	minX = fmin(fmin(fmin(ent1topLeft.x, ent1topRight.x), ent1bottLeft.x), ent1bottRight.x);
	maxX = fmax(fmax(fmax(ent1topLeft.x, ent1topRight.x), ent1bottLeft.x), ent1bottRight.x);
	//check for x collision

	if (!(minX <= e2->width * 0.5 && maxX >= -e2->width * 0.5)) 
	{
		return false;
	}
	//get min y and max y
	minY = fmin(fmin(fmin(ent1topLeft.y, ent1topRight.y), ent1bottLeft.y), ent1bottRight.y);
	maxY = fmax(fmax(fmax(ent1topLeft.y, ent1topRight.y), ent1bottLeft.y), ent1bottRight.y);
	//check for y collision
	if (!(minY <= e2->height * 0.5 && maxY >= -e2->height * 0.5)) 
	{
		return false;
	}

	return true;
}

bool GameManager::isGameOver()
{
	return gameOver;
}

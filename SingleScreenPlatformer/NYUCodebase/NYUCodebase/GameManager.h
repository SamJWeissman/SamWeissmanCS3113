#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "Entity.h"
#include "Player.h"
#include "DrawingManager.h"
#include "EntityManager.h"
#include <vector>

class GameManager
{
public:
	GameManager();
	~GameManager();
	void setupGL();
	void setupGameVariables();
	void init();
	void updateAndRender();
	void fixedLoop();
	void fixedUpdate();
	void update(float elapsed);
	void render();
	void renderGameLost();
	void renderStartScreen();
	void processEvents(SDL_Event &event);
	void handleYPenetration(Entity* entity, std::vector<Entity*> entities);
	void handleXPenetration(Entity* entity, std::vector<Entity*> entities);
	bool isGameOver();

private:

	bool gameOver;
	bool playerLost;
	bool gameRunning;
	int state;
	float ticks;
	float lastFrameTicks;
	float elapsed;
	float timeLeftOver;
	int lavaBlobCounter;

	Player* player;
	DrawingManager* drawingMgr;
	EntityManager* entityMgr;
	std::vector<Entity*> entities;
	std::vector<Entity*> prizes;
	SDL_Window* displayWindow;

};

#endif
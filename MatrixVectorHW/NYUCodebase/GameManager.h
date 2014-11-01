#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "Entity.h"
#include "Player.h"
#include "DrawingManager.h"
//#include "EntityManager.h"
//#include <SDL_mixer.h>
#include <vector>

#define LEVEL_HEIGHT 16
#define LEVEL_WIDTH 64
#define TILE_SIZE .233f
#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6

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
	//void obstacle(int x);
	void processEvents(SDL_Event &event);
	void handleYPenetration(Entity* entity, std::vector<Entity*> entities);
	void handleXPenetration(Entity* entity, std::vector<Entity*> entities);
	//void worldToTileCoordinates(float worldX, float worldY, int *gridX, int *gridY);
	//void checkYlevelCollision(Entity* entity);
	//void checkXlevelCollision(Entity* entity);
	//float pointAndGridCollisionXaxis(float x, float y);
	//float pointAndGridCollisionYaxis(float x, float y);
	//bool isSolid(unsigned char tile);
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
	float timer;
	//Mix_Chunk *jetPack;
	//Mix_Chunk *collectPrize;


	Player* player;
	DrawingManager* drawingMgr;
	//EntityManager* entityMgr;
	std::vector<Entity*> entities;
	//std::vector<Entity*> prizes;
	SDL_Window* displayWindow;

};

#endif
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "DrawingManager.h"
#include "EntityManager.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Bullet.h"
#include <vector>

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6

class GameManager
{
public:
	GameManager();
	~GameManager();

	void updateAndRender();
	void FixedUpdate();
	void FixedLoop();
	void adjustTime();
	void update();
	void render();
	void processEvents(SDL_Event &event);
	bool isGameOver();
	void setupGL();
	void setupGameVariables();
	void init();

private:

	GLuint spriteSheetTexture;
	bool gameOver;
	float timeLeftOver;
	float ticks;
	float lastFrameTicks;
	float elapsed;
	float screenShakeTime;
	float timeStillShooting;
	int waveCounter;
	int state;
	const Uint8 *keys;
	std::vector<Bullet*> enemyBullets;
	int enemyBulletCounter;
	DrawingManager* drawingManager;
	EntityManager* entityManager;
	CollisionManager* collisionManager;
	Player* player;
	SDL_Window* displayWindow;
};

#endif
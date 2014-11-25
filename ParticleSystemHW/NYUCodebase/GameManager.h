#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "DrawingManager.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Player.h"
#include "Bullet.h"
#include "CollisionManager.h"
#include "Star.h"

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
	float shakeIntensity;
	float timeStillShooting;
	float clearRed;
	float clearGreen;
	float clearBlue;
	float standardClearColor;
	float killCountTimer;
	float killSpreeCount;
	int waveCounter;
	int state;
	const Uint8 *keys;
	std::vector<Bullet*> enemyBullets;
	std::vector<Star> stars;
	int enemyBulletCounter;
	Mix_Music *gameSong;
	Mix_Chunk *explode1;
	Mix_Chunk *explode2;
	Mix_Chunk *explode3;
	Mix_Chunk *explode4;
	Mix_Chunk *playerShoot;
	Mix_Chunk *badGuyShoot;
	Mix_Chunk *hit1;
	Mix_Chunk *hit2;
	Mix_Chunk *hit3;
	Mix_Chunk *rocket;
	Mix_Chunk *badGuyDodge;
	Mix_Chunk *clusterWave;
	Mix_Chunk *sneakyWave;
	Mix_Chunk *doubleKill;
	Mix_Chunk *tripleKill;
	Mix_Chunk *multiKill;
	Mix_Chunk *ultraKill;
	Mix_Chunk *monsterKill;
	DrawingManager* drawingManager;
	EntityManager* entityManager;
	CollisionManager* collisionManager;
	Player* player;
	SDL_Window* displayWindow;
};

#endif
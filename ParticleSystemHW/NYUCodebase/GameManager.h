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
	void render();
	void processEvents(SDL_Event &event);
	void setupGL();
	void setupGameVariables();
	void init();
	void initManagers();
	void initAudio();
	void initGameTimers();
	void initClearColors();
	void initGameCounters();
	void initEnemyBullets();
	void initPlayer();
	void initStars();
	void initClockVariables();
	void updateGameTimers();
	void updateStars();
	void updateBullets();
	void resetTimers();
	void handleEnemyBreakthrough();
	void handleEnemyBreakthroughSpree();
	void breakthroughActions();
	void handleNoKillingSpree();
	void renderStars();
	void renderScreenShake();
	void renderAlienClown();
	void renderEntities();
	void renderEnemyBullets();
	void renderPlayerBullets();
	void renderBullets();
	void renderBoost();
	void renderWarp();
	void renderStartScreenAnimation();
	void renderPlayerLostAnimation();
	void enemyBulletsFire(int i);
	void clearScreen();
	void resetClearColors();
	void startGame();
	void playerFire();
	void enemyDodge();
	void handlePollEvents(SDL_Event &event);
	void spawnClusterWave();
	void spawnSpecialEntity();
	void spawnNormalWaves();
	void handlePlayerDeath();
	void handlePlayerHasBigGun();
	void handleEnemyWasHit();
	void enemyHitActions();
	void killingSpreeActions();
	void handlePlayerShot();
	void handlePlayerEnemyCollision();
	void handlePlayerWarp();

	bool checkPlayerWasShot();
	bool checkPlayerWarped();
	bool checkPlayerEnemyCollision();
	bool potentialKillingSpree();
	bool checkIfEnemyWasHit();
	bool checkForBigGun();
	bool checkForPlayerDeath();
	bool checkForBreakthroughSpree();
	bool checkForEnemyBreakthrough();
	bool isGameOver();
	//void adjustTime();

private:

	GLuint spriteSheetTexture;
	bool gameOver;
	float alienLaughTimer;
	float timeLeftOver;
	float ticks;
	float lastFrameTicks;
	float elapsed;
	float screenShakeTime;
	float bigGunTimer;
	float shakeIntensity;
	float timeStillShooting;
	float clearRed;
	float clearGreen;
	float clearBlue;
	float standardClearColor;
	float killCountTimer;
	bool stopLoseSound;
	int killSpreeCount;
	float enemyBreakthroughCount;
	float enemyBreakthroughTimer;
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
	Mix_Chunk *alienLaugh;
	Mix_Chunk *dieLaugh;
	Mix_Chunk *playerLost;
	Mix_Chunk *bigGun;
	Mix_Chunk *warp;
	DrawingManager* drawingManager;
	EntityManager* entityManager;
	CollisionManager* collisionManager;
	Player* player;
	SDL_Window* displayWindow;
};

#endif
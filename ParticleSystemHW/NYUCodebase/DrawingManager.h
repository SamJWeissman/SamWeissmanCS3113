#ifndef _DRAWINGMANAGER_H_
#define _DRAWINGMANAGER_H_
#include <string>
#include "Entity.h"
#include "Bullet.h"
#include "Star.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class DrawingManager
{
public:
	typedef struct {
		float x;
		float y;
		float r;
		float g;
		float b;
		float a;
	} Vertex2D;

	DrawingManager();
	~DrawingManager();
	void DrawBoost(float x, float y);
	void DrawAlienFace(int textureNum);
	void DrawSomeText(std::string text, float x, float y, float size, float spacing, float r, float g, float b, float a);
	void DrawSprite(GLuint texture, float x, float y, float width, float height, float rotation);
	void DrawSheetSprite(Entity* entity);
	void DrawBullet(Bullet* bullet, bool isEnemy);
	void DrawStar(Star star);
	void DrawBulletTrail(Bullet* bullet, bool isEnemy);
	void DrawEnemyEngineTrail(Entity* entity);
	void shakeScreen(float elapsed, float shakeSpeed, float shakeIntensity);
	void stopScreenShake();
	GLuint LoadTexture(const char *img_path);
	void DrawStatBoard(int health, int waveCounter, int score);
	void DrawStartScreen();
	void DrawYouLose(int score);
	void DrawYouWin(int score);
	void DrawWarp(float warpX, float elapsed);
	void SamWeissman();
	bool getSWComplete();
	void Presents();
	bool getPresentsComplete();
	void SpaceInvaders();
	bool getSpaceInvadersComplete();
	void ShowControls();
	bool getShowControlsComplete();
	bool getStartScreenReady();

private:
	GLuint fontTexture;
	GLuint spriteSheetTexture;
	GLuint alienFace;
	GLuint deathSpreeFace;
	GLuint alienHostage;
	bool samWeissmanDone;
	bool presentsDone;
	bool spaceInvadersDone;
	bool showControlsDone;
	bool startScreenReady;
	float rotation;
	float textTimer;
	float screenShakeValue;
	float screenShakeSpeed;
	float screenShakeIntensity;
};

#endif
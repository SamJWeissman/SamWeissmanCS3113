#ifndef _DRAWINGMANAGER_H_
#define _DRAWINGMANAGER_H_
#include <string>
#include "Entity.h"
//#include "Bullet.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#define LEVEL_HEIGHT 16
#define LEVEL_WIDTH 64
#define TILE_SIZE .233f
#define SPRITE_COUNT_Y 8
#define SPRITE_COUNT_X 16

class DrawingManager
{
public:
	typedef struct {
		float x;
		float y;
		float r;
		float g;
		float b;
	} Vertex2D;

	DrawingManager();
	~DrawingManager();
	void DrawQuad(float width, float height, float x, float y, float r, float g, float b);
	void DrawStaticEntity(Entity* entity);
	void DrawPrize(Entity* entity);
	void DrawLavaBlob(Entity* entity);
	void DrawRocketBoost(float x, float y);
	void DrawSomeText(std::string text, float x, float y, float size, float spacing, float r, float g, float b, float a);
	void DrawSprite(GLuint texture, float x, float y, float width, float height, float rotation);
	void DrawSheetSpriteNonUniform(Entity* entity);
	void DrawSheetSpriteUniform(Entity* entity, int index);
	//void DrawBullet(Bullet* bullet);
	GLuint LoadTexture(const char *img_path);
	void DrawStatBoard(int energy, int score);
	void DrawStartScreen();
	void DrawYouLose(int score, float xZone);
	void DrawYouWin(int score);
	void DrawTileLevel(unsigned char levelData[LEVEL_HEIGHT][LEVEL_WIDTH], float zone);

	GLuint fontTexture;
	GLuint spriteSheetTexture;
	GLuint levelSheetTexture;
	GLuint explosionTexture;
};

#endif
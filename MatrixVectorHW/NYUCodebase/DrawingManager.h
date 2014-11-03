#ifndef _DRAWINGMANAGER_H_
#define _DRAWINGMANAGER_H_
#include <string>
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
	void DrawQuad(float width, float height, float r, float g, float b);
	void DrawTriangle(float width, float height);
	void DrawSheetSpriteUniform(float width, float height, int index);
	GLuint LoadTexture(const char *img_path);
	GLuint spriteSheetTexture;
};

#endif
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <stdlib.h>

using namespace std;

SDL_Window* displayWindow;

typedef struct {
	float x;
	float y;
	float r;
	float g;
	float b;
} Vertex2D;

GLuint LoadTexture(const char *image_path)
{
	SDL_Surface *surface = IMG_Load(image_path);
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);
	return textureID;
}

void DrawSprite(GLint texture, float x, float y, float rotation)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0);
	glRotatef(rotation, 0.0, 0.0, 1.0);
	GLfloat quad[] = { -0.1f, 0.1f, -0.1f, -0.1f, 0.1f, -0.1f, 0.1f, 0.1f };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat quadUVs[] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 }; 
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
}

void DrawWall(GLint texture, float x, float y)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0);
	GLfloat quad[] = { -0.1f, 1.5f, -0.1f, -1.5f, 0.1f, -1.5f, 0.1f, 1.5f}; //larger than screen because image was distorting
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat quadUVs[] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
}

void DrawRoadAcrossScreen(GLuint texture)
{
	for (float i = -1.37f; i < 1.23; i += .2f)
	{
		DrawSprite(texture, i, 0.0f, 0.0f);
	}
}

void DrawBackgroundImages(GLuint texture[])
{

		DrawSprite(texture[0], .9f, 0.1f, 0.0f);
		DrawSprite(texture[1], 0.1f, 0.3f, 0.0f);
		DrawSprite(texture[2], 1.1f, 0.4f, 0.0f);

		DrawSprite(texture[0], -1.2f, -0.5f, 0.0f);
		DrawSprite(texture[1], 0.4f, -.7f, 0.0f);
		DrawSprite(texture[2], -0.6f, 0.3f, 0.0f);

		DrawSprite(texture[0], 0.5f, -.4f, 0.0f);
		DrawSprite(texture[1], -1.2f, 0.6f, 0.0f);
		DrawSprite(texture[2], 0.8f, -.8f, 0.0f);

		DrawSprite(texture[0], 0.2f, -.3f, 0.0f);
		DrawSprite(texture[1], -1.1f, 0.5f, 0.0f);
		DrawSprite(texture[2], 0.7f, -.8f, 0.0f);

		DrawSprite(texture[0], 0.9f, -.5f, 0.0f);
		DrawSprite(texture[1], -1.3f, 0.7f, 0.0f);
		DrawSprite(texture[2], 0.1f, -.9f, 0.0f);

		DrawSprite(texture[3], -0.25f, 0.25f, 0.0f);
		DrawSprite(texture[3], 0.25f, 0.25f, 0.0f);
		DrawSprite(texture[3], -0.25f, -0.25f, 0.0f);
		DrawSprite(texture[3], 0.25f, -0.25f, 0.0f);
		DrawSprite(texture[3], -0.75f, 0.75f, 0.0f);
		DrawSprite(texture[3], 0.75f, 0.75f, 0.0f);
		DrawSprite(texture[3], -0.75f, -0.75f, 0.0f);
		DrawSprite(texture[3], 0.75f, -0.75f, 0.0f);
		DrawSprite(texture[3], -0.35f, 0.45f, 0.0f);
		DrawSprite(texture[3], 0.45f, 0.35f, 0.0f);
		DrawSprite(texture[3], -0.35f, -0.45f, 0.0f);
		DrawSprite(texture[3], 0.45f, -0.35f, 0.0f);
		DrawSprite(texture[3], -1.25f, 0.25f, 0.0f);
		DrawSprite(texture[3], -1.15f, 0.25f, 0.0f);
		DrawSprite(texture[3], -1.30f, -0.25f, 0.0f);
		DrawSprite(texture[3], -1.05f, -0.25f, 0.0f);

}

void DrawTriangle(float x, float y, float r, float g, float b, float rotation)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0);
	glRotatef(rotation, 0.0, 0.0, 1.0);
	Vertex2D triangleData[3] = {{ 0.0f, 0.073f, r, g, b }, {-0.1f, -0.1f, r, g, b }, {0.1f, -0.1f, r, g, b }};
	glVertexPointer(2, GL_FLOAT, sizeof(float) * 5, triangleData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &triangleData[0].r);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	bool done = false;

	SDL_Event event;

	glViewport(0, 0, 800, 600); //Sept 8th -- rendering
	glMatrixMode(GL_PROJECTION); //Sept 8th -- set to projection matrix
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);//Sept 8th -- left, right, bott, top, zNear, zFar

	GLuint zombie = LoadTexture("zombie-icon.png"); //Sept 10th --
	GLuint wall = LoadTexture("rpgTile061.png");
	GLuint road = LoadTexture("roadTile6.png");
	GLuint smoke = LoadTexture("blackSmoke00.png");
	GLuint flash = LoadTexture("flash00.png");
	GLuint explosion = LoadTexture("explosion00.png");
	GLuint bush = LoadTexture("rpgTile160.png");

	GLuint backgroundImages[4] = { flash, explosion, smoke, bush };

	float xPosition = -1.33f;
	bool moveRight = true;

	float lastFrameTicks = 0.0f; //Sept 10th
	float rotation = 0.0f; //Sept 10th

	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}

		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		int iTicks = (int)SDL_GetTicks() / 1000;
		lastFrameTicks = ticks; 
		rotation += 45.0f * elapsed;

		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.5f, 1.0f, 0.2f, 0.0f); 
		glClear(GL_COLOR_BUFFER_BIT); 


		DrawWall(wall, 1.23f, -0.5f);
		DrawRoadAcrossScreen(road);
		DrawBackgroundImages(backgroundImages);

		for (float i = -.9; i < 1.0; i += .3f){
			DrawTriangle(1.18f, i, (rand() % 100) * .01f, (rand() % 100) * .01f, (rand() % 100) * .01f, rotation);
		}

		if (moveRight)
		{
			for (float i = -0.9f; i < 1.0f; i += 0.3f){
				DrawSprite(zombie, xPosition, i, 0.0f);
			}
			
			xPosition += .005f;
			if (xPosition > 1.03f)
			{
				moveRight = false;
			}
		}
		else
		{
			for (float i = -0.9f; i < 1.0f; i += 0.3f){
				DrawSprite(zombie, xPosition, i, 0.0f);
			}
			xPosition -= .005f;
			if (xPosition < -1.23f)
			{
				moveRight = true;
			}
		}
		SDL_GL_SwapWindow(displayWindow);
	}

	SDL_Quit();
	return 0;
}
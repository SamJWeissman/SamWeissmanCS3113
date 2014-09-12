#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <vector>

using namespace std;

SDL_Window* displayWindow;

typedef struct {
	float x;
	float y;
	float r;
	float g;
	float b;
} Vertex2D;

typedef struct {
	float x;
	float y;
} CoordHolder;

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

void drawWall(GLint texture, float x, float y)
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

void drawRoadAcrossScreen(GLuint texture)
{
	for (float i = -1.37f; i < 1.23; i += .2f)
	{
		DrawSprite(texture, i, 0.0f, 0.0f);
	}
}

void drawBackgroundBushes(vector<CoordHolder> &positions, GLuint texture)
{
	for (unsigned i = 0; i < positions.size() ; i++)
	{
		DrawSprite(texture, positions[i].x, positions[i].y, 0.0f);
	}
}

void drawTriangle(float x, float y, float r, float g, float b, float rotation)
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

void drawEndZone()
{
	for (float i = -.9; i < 1.0f; i += .3f)
	{
		drawTriangle(1.23f, i, (rand() % 100) * .01f, (rand() % 100) * .01f, (rand() % 100) * .01f, 0.0f);
	}
}

void fillPositions(vector<CoordHolder> &positions)
{
	CoordHolder temp;
	for (int i = 0; i < 80; i++)
	{
		if (i < 20)
		{
			temp.x = rand() % 133 * -0.01f;
			temp.y = rand() % 100 * 0.01f;
			positions.push_back(temp);
		}
		else if (i >= 20 && i < 40)
		{
			temp.x = rand() % 113 * 0.01f;
			temp.y = rand() % 100 * 0.01f;
			positions.push_back(temp);
		}
		else if (i >= 40 && i < 60)
		{
			temp.x = rand() % 113 * 0.01f;
			temp.y = rand() % 100 * -0.01f;
			positions.push_back(temp);
		}
		else
		{
			temp.x = rand() % 133 * -0.01f;
			temp.y = rand() % 100 * -0.01f;
			positions.push_back(temp);
		}
	}
}

class Zombie {
public:
	float x;
	float y;
	bool moveRight = true;
	bool alive = true;
	GLuint zombieTexture = LoadTexture("zombie-icon.png");
	Zombie(float xPos, float yPos) : x(xPos), y(yPos){}

	void moveZombie()
	{
		if (moveRight)
		{
			x += rand() % 50 * .0001f;
			if (x > 1.03f)
			{
				moveRight = false;
			}
		}
		else
		{
			x -= rand() % 50 * .0001f;
			if (x < -1.23f)
			{
				moveRight = true;
			}
		}
	}
};

void moveZombieHorde(vector<Zombie*> &zombies)
{
	for (unsigned i = 0; i < zombies.size(); i++)
	{
		if (zombies[i]->alive)
		{
			DrawSprite(zombies[i]->zombieTexture, zombies[i]->x, zombies[i]->y, 0.0f);
			zombies[i]->moveZombie();
		}
	}
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
	
	GLuint wall = LoadTexture("rpgTile061.png");
	GLuint road = LoadTexture("roadTile6.png");
	GLuint bush = LoadTexture("rpgTile160.png");

	vector<CoordHolder> positions;
	fillPositions(positions);
	
	vector<Zombie*> zombies;
	for (float i = -.9f; i < 1.0f; i += .3f)
	{
		Zombie *z = new Zombie(-1.33f, i);
		zombies.push_back(z);
	}

	float lastFrameTicks = 0.0f;
	//float rotation = 0.0f; //Sept 10th

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
		//rotation += 45.0f * elapsed;

		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.5f, 1.0f, 0.2f, 0.0f); 
		glClear(GL_COLOR_BUFFER_BIT); 

		drawWall(wall, 1.23f, -0.5f);
		drawRoadAcrossScreen(road);
		drawBackgroundBushes(positions, bush);
		drawEndZone();
		moveZombieHorde(zombies);

		SDL_GL_SwapWindow(displayWindow);
	}

	SDL_Quit();
	return 0;
}
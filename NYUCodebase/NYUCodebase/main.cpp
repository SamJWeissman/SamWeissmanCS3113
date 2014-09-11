#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

using namespace std;

SDL_Window* displayWindow;

GLuint LoadTexture(const char *image_path) 
{
	SDL_Surface *surface = IMG_Load(image_path);
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//delete surface;
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
	GLfloat quad[] = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f };
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
	
	GLuint testTexture = LoadTexture("cardSpadesA.png"); //Sept 10th --
	float lastFrameTicks = 0.0f; //Sept 10th
	float faceRotation = 0.0f; //Sept 10th

	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}

		float ticks = (float)SDL_GetTicks()/100.f; // Sept 10th
		float elapsed = ticks - lastFrameTicks; //Sept 10th
		lastFrameTicks = ticks; //Sept 10th
		//faceRotation += 45.0f * elapsed; //Sept 10th

		glMatrixMode(GL_MODELVIEW); //Sept 8th -- called inside loop before transformations because when things get complex, we cant be positive the matrix hasnt been changed

		//glLoadIdentity(); //Sept 8th -- reset
		//glTranslatef(1.0, 0.0, 0.0); //Sept 8th -- move right
		//glLoadIdentity(); //Sept 8th
		//glRotatef(45.0f, 0.0, 0.0, 1.0); //Sept 8th -- rortate 45 degrees  
		//glLoadIdentity(); //Sept 8th
		//glScalef(2.0, 1.0, 1.0); //Sept 8th -- scale (obviously)

		//glLoadIdentity(); //Sept 10th
		//glTranslatef(-0.5f, 0.0f, 0.0f); //Sept 10th

		glClearColor(0.4f, 0.2f, 0.4f, 1.0f); //Sept 10th -- Sets clear color of the screen, purple in this example
		glClear(GL_COLOR_BUFFER_BIT); //Sept 10th -- Clears screen to clear color

		/*GLfloat triangle[] = { 0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f }; //Sept 8th -- counter-clock wise
		glVertexPointer(2, GL_FLOAT, 0, triangle); //Sept 8th -- size (how many points at each vertex), type, stride (how much to skip in array), array of vertex pos'n
		glEnableClientState(GL_VERTEX_ARRAY);//Sept 8th -- lets GL know that the vertex array has been defined

		GLfloat triangleColors[] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 }; //Sept 10th
		glColorPointer(3, GL_FLOAT, 0, triangleColors); //Sept 10th -- definies an array of vertex color data
		glEnableClientState(GL_COLOR_ARRAY); //Sept 10th

		glDrawArrays(GL_TRIANGLES, 0, 3); //Sept 8th -- self explanatory

		glLoadIdentity(); //Sept 10th
		glTranslatef(0.5f, 0.0f, 0.0f); //Sept 10th
		glDisableClientState(GL_COLOR_ARRAY); //Sept 10th

		GLfloat quad[] = { 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f }; //Sept 10th
		glVertexPointer(2, GL_FLOAT, 0, quad); //Sept 10th
		glEnableClientState(GL_VERTEX_ARRAY); //Sept 10th

		//did texture stuff here //Sept 10th
		//did blend stuff here //Sept 10th

		glDrawArrays(GL_QUADS, 0, 4); //Sept 10th*/

		DrawSprite(testTexture, 0.0, 0.0, 0.0);

		SDL_GL_SwapWindow(displayWindow);
	}

	SDL_Quit();
	return 0;
}
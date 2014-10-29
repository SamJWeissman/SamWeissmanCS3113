
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Matrix.h"
#include "Vector.h"

SDL_Window* displayWindow;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	Matrix* m1 = new Matrix();
	Matrix* m2 = new Matrix();
	
	for (int i = 0; i < 16; i++)
	{
		m1->ml[i] = 2;
		m2->ml[i] = 3;
	}

	Matrix m3 = (*m1) * (*m2);
	Vector* v1 = new Vector();

	v1->x = 1;
	v1->y = 1;
	v1->z = 1;

	Vector v2 = (*m1) * (*v1);
	v2.normalize();

	bool done = false;
	SDL_Event event;

	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}


		SDL_GL_SwapWindow(displayWindow);
	}

	

	SDL_Quit();
	return 0;
}
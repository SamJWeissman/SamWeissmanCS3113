#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "GameManager.h"

SDL_Window* displayWindow;

int main(int argc, char *argv[])
{
	SDL_Event event;
	GameManager *gameManager = new GameManager();
	gameManager->init();

	while (!gameManager->isGameOver()) {
		gameManager->processEvents(event);
		gameManager->updateAndRender();
	}

	SDL_Quit();
	return 0;
}
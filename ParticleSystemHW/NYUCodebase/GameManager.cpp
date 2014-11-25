#pragma once
#include "GameManager.h"


enum GAMESTATE { STATE_START_SCREEN, STATE_GAME_RUNNING, STATE_GAME_LOSE, STATE_GAME_WIN };

GameManager::GameManager(){
	state = STATE_START_SCREEN;
}
GameManager::~GameManager(){}

void GameManager::init()
{
	setupGL();
	setupGameVariables(); 
}

void GameManager::setupGL()
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
}

void GameManager::setupGameVariables()
{
	gameOver = false;
	player = new Player();
	drawingManager = new DrawingManager();
	entityManager = new EntityManager(player);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	
	gameSong = Mix_LoadMUS("themeSong.wav");
	explode1 = Mix_LoadWAV("explode1.wav");
	explode2 = Mix_LoadWAV("explode2.wav");
	explode3 = Mix_LoadWAV("explode3.wav");
	explode4 = Mix_LoadWAV("explode4.wav");
	playerShoot = Mix_LoadWAV("playerShoot.wav");
	badGuyShoot = Mix_LoadWAV("badGuyShoot.wav");
	badGuyDodge = Mix_LoadWAV("badGuyDodge.wav");
	clusterWave = Mix_LoadWAV("clusterWave.wav");
	sneakyWave = Mix_LoadWAV("sneakyWave.wav");
	rocket = Mix_LoadWAV("rocket.wav");
	hit1 = Mix_LoadWAV("hit1.wav");
	hit2 = Mix_LoadWAV("hit2.wav");
	hit3 = Mix_LoadWAV("hit3.wav");
	doubleKill = Mix_LoadWAV("doublekill.wav");
	tripleKill = Mix_LoadWAV("triplekill.wav");
	multiKill = Mix_LoadWAV("multikill.wav");
	ultraKill = Mix_LoadWAV("ultrakill.wav");
	monsterKill = Mix_LoadWAV("monsterkill.wav");

	Mix_PlayMusic(gameSong, -1);
	for (int i = 0; i < 40; i++)
	{
		enemyBullets.push_back(new Bullet(true));
	}
	enemyBulletCounter = 0;

	for (int i = 0; i < 10; i++)
	{
		float size = rand() % 20 * .01f;
		Star quadOneStar(-1.33f + rand() % 133 * .01f, 1.0f - rand() % 100 * .01f, size);
		Star quadTwoStar(0.0f + rand() % 133 * .01f, 1.0f - rand() % 100 * .01f, size);
		Star quadThreeStar(-1.33f + rand() % 133 * .01f, 0.0f - rand() % 100 * .01f, size);
		Star quadFourStar(0.0f + rand() % 133 * .01f, 0.0f - rand() % 100 * .01f, size);

		stars.push_back(quadOneStar);
		stars.push_back(quadTwoStar);
		stars.push_back(quadThreeStar);
		stars.push_back(quadFourStar);
	}

	collisionManager = new CollisionManager(enemyBullets, entityManager, player);

	waveCounter = 0;
	screenShakeTime = 0.0f;

	lastFrameTicks = 0.0f;
	elapsed = 0.0f;
	timeLeftOver = 0.0f;

	killSpreeCount = 0.0f;
	killCountTimer = 0.0f;

	standardClearColor = 0.0f;
	clearRed = standardClearColor;
	clearGreen = standardClearColor;
	clearBlue = standardClearColor;


	entityManager->pushEntity(player->getSpaceship());
}

void GameManager::FixedUpdate()
{
	for (int i = 0; i < entityManager->numEntities(); i++)
	{
		entityManager->getEntityAt(i)->FixedUpdate();
		entityManager->getEntityAt(i)->moveY();
		entityManager->getEntityAt(i)->moveX();
	}
}

void GameManager::FixedLoop()
{
	ticks = (float)SDL_GetTicks() / 1000.0f;
	elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	float fixedElapsed = elapsed + timeLeftOver;
	if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS) {
		fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
	}

	while (fixedElapsed >= FIXED_TIMESTEP) {
		fixedElapsed -= FIXED_TIMESTEP;
		FixedUpdate();
	}
	timeLeftOver = fixedElapsed;
}

void GameManager::adjustTime()
{
	ticks = (float)SDL_GetTicks() / 1000.0f;
	elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;
}

void GameManager::update()
{
	if (state == STATE_GAME_RUNNING)
	{
		for (int i = 0; i < 40; i++)
		{
			enemyBullets[i]->update(elapsed);
			((player->getBullets())[i])->update(elapsed);
			stars[i].update(elapsed, waveCounter);
		}
		entityManager->updateEmitters(elapsed);
		if (entityManager->enemyShipBrokeThrough())
		{
			Mix_PlayChannel(-1, hit3, 0);
			screenShakeTime = 0.0f;
			shakeIntensity = 3.0f;
			clearRed = 1.0f;
		}
		killCountTimer -= elapsed;
		if (killCountTimer <= 0.0f)
		{
			killSpreeCount = 0;
		}
	}
}

void GameManager::render()
{
	glClearColor(clearRed, clearGreen, clearBlue, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (screenShakeTime < 1.0f)
	{
		drawingManager->shakeScreen(elapsed, 20.0f, shakeIntensity);
		screenShakeTime += elapsed;
	}

	if (state == STATE_GAME_RUNNING)
	{
		for (int i = 0; i < entityManager->numEntities(); i++)
		{
			drawingManager->DrawSheetSprite(entityManager->getEntityAt(i));
			if (i > 0)
			{
				drawingManager->DrawEnemyEngineTrail(entityManager->getEntityAt(i));
			}
			if (i > 0 && rand() % 1000 >= 995)
			{
				Mix_PlayChannel(-1, badGuyShoot, 0);
				enemyBullets[i]->fire((entityManager->getEntityAt(i))->getX(), (entityManager->getEntityAt(i))->getY());
			}
			drawingManager->DrawBullet(enemyBullets[i]);
		}
		for (int i = 0; i < player->getBullets().size(); i++)
		{
			drawingManager->DrawBullet((player->getBullets())[i]);
			drawingManager->DrawBulletTrail((player->getBullets())[i]);
		}
		drawingManager->DrawStatBoard(player->getHealth(), waveCounter, player->getScore());
		entityManager->renderParticles();
		if (player->getBoost())
		{
			float x = player->getSpaceship()->getX();
			float y = player->getSpaceship()->getY();
			drawingManager->DrawBoost(x, y);
			Mix_PlayChannel(-1, rocket, 0);
		}
		for (int i = 0; i < stars.size(); i++)
		{
			drawingManager->DrawStar(stars[i]);
		}
	}
	else if (state == STATE_START_SCREEN)
	{
		drawingManager->DrawStartScreen();
	}
	else if (state == STATE_GAME_LOSE)
	{
		drawingManager->DrawYouLose(player->getScore());
	}
	else if (state == STATE_GAME_WIN)
	{
		drawingManager->DrawYouWin(player->getScore());
	}

	SDL_GL_SwapWindow(displayWindow);

	clearRed = standardClearColor;
	clearBlue = standardClearColor;
	clearGreen = standardClearColor;
}

void GameManager::updateAndRender()
{

	update();
	FixedLoop();
	render();
}

void GameManager::processEvents(SDL_Event &event)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
		{
			gameOver = true;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (state != STATE_GAME_RUNNING)
			{
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				{
					state = STATE_GAME_RUNNING;
					player->resetScore();
					entityManager->getEntityAt(0)->setX(0.0f);
					entityManager->orangeWave();
					waveCounter++;
				}
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_LCTRL)
			{
				player->shoot();
				Mix_PlayChannel(-1, playerShoot, 0);
				for (int i = 1; i < entityManager->numEntities(); i++)
				{
					Entity* ent = entityManager->getEntityAt(i);
					float diff = abs(player->getSpaceship()->getX() - ent->getX());
					if (diff < .1f && rand() % 1000 < 50)
					{
						Mix_PlayChannel(-1, badGuyDodge, 0);
						if (ent->getX() < -0.0f)
						{
							ent->bankRight();
						}
						else
						{
							ent->bankLeft();
						}
					}
				}
			}
		}
	}
	if (state == STATE_GAME_RUNNING){
		if (entityManager->numEntities() < 10 && rand() % 1000 > 995)
		{
			int val = rand() % 10;
			if (val < 5)
			{
				Mix_PlayChannel(-1, sneakyWave, 0);
				entityManager->sneakyWave();
			}
			else if (val > 5)
			{
				Mix_PlayChannel(-1, clusterWave, 0);
				entityManager->clusterWave();
			}
		}
		if (entityManager->numEntities() < 2)
		{
			if (waveCounter % 3 == 1)
			{
				entityManager->greenWave();
				waveCounter++;
			}
			else if (waveCounter % 3 == 2)
			{
				entityManager->blueWave();
				waveCounter++;
			}
			else if (waveCounter % 3 == 0)
			{
				entityManager->increaseSpeed();
				entityManager->orangeWave();
				waveCounter++;
			}
		}

		player->checkInputControls();

		if (player->getHealth() <= 0)
		{
			state = STATE_GAME_LOSE;
			waveCounter = 0;
			player->setHealth(100);
		}

		if (collisionManager->bulletsVsEntities())
		{
			killCountTimer = 0.5f;
			clearRed = 1.0f;
			clearGreen = 0.5f;
			if (killCountTimer >= 0.0f && killCountTimer <= 1.0f)
			{
				killSpreeCount += 1;
			}
			int val = rand() % 10;
			if (val <= 2)
			{
				Mix_PlayChannel(-1, explode1, 0);
			}
			else if (val >= 3 && val < 6)
			{
				Mix_PlayChannel(-1, explode2, 0);
			}
			else if (val >= 6 && val < 7)
			{
				Mix_PlayChannel(-1, explode3, 0);
			}
			else
			{
				Mix_PlayChannel(-1, explode4, 0);
			}

			if (killSpreeCount == 2)
			{
				Mix_PlayChannel(-1, doubleKill, 0);
			}
			else if (killSpreeCount == 3)
			{
				Mix_PlayChannel(-1, tripleKill, 0);
			}
			else if (killSpreeCount == 4)
			{
				Mix_PlayChannel(-1, multiKill, 0);
			}
			else if (killSpreeCount == 5)
			{
				Mix_PlayChannel(-1, ultraKill, 0);
			}
			else if (killSpreeCount >= 8)
			{
				Mix_PlayChannel(-1, monsterKill, 0);
				screenShakeTime = 0.0f;
				shakeIntensity = 10.0f;
			}
		}
		if (collisionManager->bulletsVsPlayer())
		{
			Mix_PlayChannel(-1, hit1, 0);
			screenShakeTime = 0.0f;
			shakeIntensity = 1.0f;
		}
		if (collisionManager->entityVsPlayer())
		{
			Mix_PlayChannel(-1, hit2, 0);
			screenShakeTime = 0.0f;
			shakeIntensity = 3.0f;
		}
	}
}

bool GameManager::isGameOver()
{
	return gameOver;
}
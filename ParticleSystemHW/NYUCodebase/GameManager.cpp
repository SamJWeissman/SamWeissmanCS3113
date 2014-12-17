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

void GameManager::updateAndRender()
{
	FixedLoop();
	render();
}

void GameManager::FixedLoop()
{
	if (state == STATE_GAME_RUNNING)
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
}

void GameManager::render()
{
	clearScreen();
	renderStars();

	switch (state)
	{
	case STATE_GAME_RUNNING:
		drawingManager->DrawStatBoard(player->getHealth(), waveCounter, player->getScore());
		entityManager->renderParticles();

		renderScreenShake();
		renderAlienClown();
		renderEntities();
		renderBullets();
		renderBoost();
		renderWarp();
		break;

	case STATE_START_SCREEN:
		renderStartScreenAnimation();
		break;

	case STATE_GAME_LOSE:
		renderPlayerLostAnimation();
		break;

	default:
		break;
	}

	SDL_GL_SwapWindow(displayWindow);
	resetClearColors();
}

void GameManager::processEvents(SDL_Event &event)
{
	handlePollEvents(event);

	if (state == STATE_GAME_RUNNING)
	{
		spawnClusterWave();
		spawnSpecialEntity();
		spawnNormalWaves();

		handlePlayerHasBigGun();
		handlePlayerWarp();
		handleEnemyWasHit();

		handleEnemyBreakthrough();
		handlePlayerShot();
		handlePlayerEnemyCollision();
		handlePlayerDeath();
	}
}

/*
*****************************************************************************************************************************************************************************************************
*****************************************************************************************************************************************************************************************************
*****************************************************************************************************************************************************************************************************
---------------------------------------------------------------------------------------HELPER FUNCTIONS----------------------------------------------------------------------------------------------
*****************************************************************************************************************************************************************************************************
*****************************************************************************************************************************************************************************************************
*****************************************************************************************************************************************************************************************************
*/

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------INITIALIZATION HELPERS--------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

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

	initAudio();
	initEnemyBullets();
	initPlayer();
	initManagers();
	initGameTimers();
	initClearColors();
	initClockVariables();
	initStars();
}

void GameManager::initAudio()
{
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
	alienLaugh = Mix_LoadWAV("alienLaugh.wav");
	dieLaugh = Mix_LoadWAV("deathSpree.wav");
	playerLost = Mix_LoadWAV("playerLostSound.wav");
	bigGun = Mix_LoadWAV("bigGun.wav");
	warp = Mix_LoadWAV("warp.wav");
	Mix_PlayMusic(gameSong, -1);
}

void GameManager::initEnemyBullets()
{
	for (int i = 0; i < 40; i++)
	{
		enemyBullets.push_back(new Bullet(true));
	}
}

void GameManager::initPlayer()
{
	player = new Player();
}

void GameManager::initManagers()
{
	drawingManager = new DrawingManager();
	entityManager = new EntityManager(player);
	entityManager->pushEntity(player->getSpaceship());
	collisionManager = new CollisionManager(enemyBullets, entityManager, player);
}

void GameManager::initClearColors()
{
	standardClearColor = 0.0f;
	clearRed = standardClearColor;
	clearGreen = standardClearColor;
	clearBlue = standardClearColor;
}

void GameManager::initGameTimers()
{
	killCountTimer = 0.0f;
	screenShakeTime = 0.0f;
	alienLaughTimer = 0.0f;
	enemyBreakthroughTimer = 0.0f;
	bigGunTimer = 0.0f;

}

void GameManager::initClockVariables()
{
	lastFrameTicks = 0.0f;
	elapsed = 0.0f;
	timeLeftOver = 0.0f;
}

void GameManager::initGameCounters()
{
	enemyBulletCounter = 0;
	waveCounter = 0;
	enemyBreakthroughCount = 0;
	killSpreeCount = 0;
}

void GameManager::initStars()
{
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
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------UPDATE HELPERS-------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void GameManager::FixedUpdate()
{
	for (int i = 0; i < entityManager->numEntities(); i++)
	{
		entityManager->getEntityAt(i)->FixedUpdate();
		entityManager->getEntityAt(i)->moveY();
		entityManager->getEntityAt(i)->moveX();
	}
	updateStars();
	updateGameTimers();
	updateBullets();
}

void GameManager::updateGameTimers()
{
	if (killCountTimer > 0.0f)
	{
		killCountTimer -= FIXED_TIMESTEP;
	}
	alienLaughTimer -= FIXED_TIMESTEP;
	enemyBreakthroughTimer -= FIXED_TIMESTEP;
	screenShakeTime -= FIXED_TIMESTEP;
	bigGunTimer -= FIXED_TIMESTEP;
}

void GameManager::updateStars()
{
	for (int i = 0; i < 40; i++)
	{
		stars[i].update(FIXED_TIMESTEP, waveCounter);
	}
}

void GameManager::updateBullets()
{
	for (int i = 0; i < 40; i++)
	{
		enemyBullets[i]->update(FIXED_TIMESTEP);
		((player->getBullets())[i])->update(FIXED_TIMESTEP);
	}
	entityManager->updateEmitters(FIXED_TIMESTEP);
}

void GameManager::resetTimers()
{
	killCountTimer = 0.0f;
	alienLaughTimer = 0.0f;
	enemyBreakthroughTimer = 0.0f;
	screenShakeTime = 0.0f;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------HANDLER FUNCTIONS-------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


void GameManager::handleEnemyBreakthrough()
{
	if (checkForEnemyBreakthrough())
	{
		handleEnemyBreakthroughSpree();
		breakthroughActions();
	}
}

void GameManager::handleEnemyBreakthroughSpree()
{
	if (checkForBreakthroughSpree())
	{
		alienLaughTimer = 0.75f;
	}
}

void GameManager::handleNoKillingSpree()
{
	if (killCountTimer <= 0.0f)
	{
		killSpreeCount = 0;
	}
}

void GameManager::handlePollEvents(SDL_Event &event)
{

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
		{
			gameOver = true;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_LCTRL)
			{
				playerFire();
				enemyDodge();
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
			{
				SDL_SetWindowFullscreen(displayWindow, SDL_WINDOW_FULLSCREEN); // set
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_W)
			{

				SDL_SetWindowFullscreen(displayWindow, 0);
			}
			if (state != STATE_GAME_RUNNING)
			{
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				{
					startGame();
				}
			}
		}
	}

	player->checkInputControls();
}

void GameManager::handlePlayerDeath()
{
	if (checkForPlayerDeath())
	{
		state = STATE_GAME_LOSE;
		resetTimers();
		entityManager->resetSpeed();
		waveCounter = 0;
		player->setHealth(100);
	}
}

void GameManager::handlePlayerHasBigGun()
{
	if (checkForBigGun())
	{
		bigGunTimer = 7.0f;
		player->setBigGun(false);
	}
}

void GameManager::handleEnemyWasHit()
{
	if (checkIfEnemyWasHit())
	{
		enemyHitActions();
	}
	if (!potentialKillingSpree())
	{
		killingSpreeActions();
		killSpreeCount = 0;
	}
}

void GameManager::handlePlayerShot()
{
	if (checkPlayerWasShot())
	{
		Mix_PlayChannel(-1, hit1, 0);
		screenShakeTime = 1.0f;
		shakeIntensity = 1.0f;
	}
}

void GameManager::handlePlayerEnemyCollision()
{
	if (checkPlayerEnemyCollision())
	{
		Mix_PlayChannel(-1, hit2, 0);
		screenShakeTime = 1.0f;
		shakeIntensity = 3.0f;
	}
}

void GameManager::handlePlayerWarp()
{
	if (checkPlayerWarped())
	{
		clearBlue = 1.0f;
		Mix_PlayChannel(-1, warp, 0);
		player->setWarped(false);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------CONDITION CHECK FUNCTIONS-------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

bool GameManager::checkForEnemyBreakthrough()
{
	if (entityManager->enemyShipBrokeThrough())
	{
		return true;
	}
	return false;
}

bool GameManager::checkForBreakthroughSpree()
{
	if (enemyBreakthroughTimer > 0.0f)
	{
		enemyBreakthroughCount += 1;
		if (enemyBreakthroughCount >= 3)
		{
			return true;
		}
		return false;
	}
	enemyBreakthroughCount = 0;
	return false;
}

bool GameManager::checkForPlayerDeath()
{
	if (player->getHealth() <= 0)
	{
		return true;
	}
	return false;
}

bool GameManager::checkForBigGun()
{
	if (player->getBigGun())
	{
		return true;
	}
	return false;
}

bool GameManager::checkIfEnemyWasHit()
{
	if (collisionManager->bulletsVsEntities())
	{
		return true;
	}
	return false;
}

bool GameManager::checkPlayerWasShot()
{
	if (collisionManager->bulletsVsPlayer())
	{
		return true;
	}
	return false;
}

bool GameManager::checkPlayerEnemyCollision()
{
	if (collisionManager->entityVsPlayer())
	{
		return true;
	}
	return false;
}

bool GameManager::checkPlayerWarped()
{
	if (player->playerWarped())
	{
		return true;
	}
	return false;
}

bool GameManager::potentialKillingSpree()
{
	if (killCountTimer <= 0.0f)
	{
		return false;
	}
	return true;
}

bool GameManager::isGameOver()
{
	return gameOver;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------ACTIONS TAKEN FUNCTIONS---------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void GameManager::breakthroughActions()
{
	Mix_PlayChannel(-1, hit3, 0);
	screenShakeTime = 1.0f;
	shakeIntensity = 3.0f;
	clearRed = 1.0f;
	enemyBreakthroughTimer = 1.25f;
}

void GameManager::enemyBulletsFire(int i)
{
	if (i > 0 && rand() % 1000 >= 995)
	{
		Mix_PlayChannel(-1, badGuyShoot, 0);
		enemyBullets[i]->fire((entityManager->getEntityAt(i))->getX(), (entityManager->getEntityAt(i))->getY(), false);
	}
}

void GameManager::startGame()
{
	state = STATE_GAME_RUNNING;
	player->resetScore();
	entityManager->getEntityAt(0)->setX(0.0f);
	entityManager->orangeWave();
	waveCounter++;
}

void GameManager::playerFire()
{
	if (bigGunTimer > 0)
	{
		player->shoot(true);
		Mix_PlayChannel(-1, bigGun, 0);
	}
	else
	{
		player->shoot(false);
		Mix_PlayChannel(-1, playerShoot, 0);
	}
}

void GameManager::enemyDodge()
{
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

void GameManager::spawnClusterWave()
{
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
			entityManager->linearWave();
		}
	}
}

void GameManager::spawnSpecialEntity()
{
	if (entityManager->numEntities() < 15 && rand() % 1000 > 997)
	{
		entityManager->specialEnt();
	}
}

void GameManager::spawnNormalWaves()
{
	int waveMod = waveCounter % 3;
	if (entityManager->numEntities() < 2)
	{
		switch (waveMod)
		{
		case 0:
			entityManager->greenWave();
			waveCounter++;
			break;
		case 1:
			entityManager->blueWave();
			waveCounter++;
			break;
		case 2:
			entityManager->increaseSpeed();
			entityManager->orangeWave();
			waveCounter++;
			alienLaughTimer = 1.0f;
			screenShakeTime = 1.0f;
			shakeIntensity = 5.0f;
			break;
		default:
			break;
		}
	}
}

void GameManager::enemyHitActions()
{
	if (potentialKillingSpree())
	{
		killSpreeCount += 1;
	}
	else
	{
		killSpreeCount += 1;
		killCountTimer = 0.5f;
	}

	clearRed = 1.0f;
	clearGreen = 0.5f;

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
}

void GameManager::killingSpreeActions()
{
	switch (killSpreeCount)
	{
	case 2:
		Mix_PlayChannel(-1, doubleKill, 0);
		break;
	case 3:
		Mix_PlayChannel(-1, tripleKill, 0);
		break;
	case 4:
		Mix_PlayChannel(-1, ultraKill, 0);
		break;
	case 5:
		Mix_PlayChannel(-1, monsterKill, 0);
		screenShakeTime = 1.0f;
		shakeIntensity = 10.0f;
		break;
	default:
		break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------RENDER FUNCTIONS------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void GameManager::renderStars()
{
	for (int i = 0; i < stars.size(); i++)
	{
		drawingManager->DrawStar(stars[i]);
	}
}

void GameManager::renderScreenShake()
{
	if (screenShakeTime > 0.0f)
	{
		drawingManager->shakeScreen(elapsed, 20.0f, shakeIntensity);
	}
}

void GameManager::renderAlienClown()
{
	if (alienLaughTimer > 0.0f && enemyBreakthroughCount >= 2)
	{
		Mix_PlayChannel(-1, dieLaugh, 0);
		drawingManager->DrawAlienFace(1);
	}
	else if (alienLaughTimer > 0.0f)
	{
		Mix_PlayChannel(-1, alienLaugh, 0);
		drawingManager->DrawAlienFace(0);
	}
}

void GameManager::renderEntities()
{
	for (int i = 0; i < entityManager->numEntities(); i++)
	{
		drawingManager->DrawSheetSprite(entityManager->getEntityAt(i));
		if (i > 0)
		{
			drawingManager->DrawEnemyEngineTrail(entityManager->getEntityAt(i));
		}
	}
}

void GameManager::renderBullets()
{
	renderEnemyBullets();
	renderPlayerBullets();
}

void GameManager::renderEnemyBullets()
{
	for (int i = 0; i < entityManager->numEntities(); i++)
	{
		enemyBulletsFire(i);
		drawingManager->DrawBullet(enemyBullets[i], true);
		drawingManager->DrawBulletTrail(enemyBullets[i], true);
	}
}

void GameManager::renderPlayerBullets()
{
	for (int i = 0; i < player->getBullets().size(); i++)
	{
		drawingManager->DrawBullet((player->getBullets())[i], false);
		drawingManager->DrawBulletTrail((player->getBullets())[i], false);
	}
}

void GameManager::renderBoost()
{
	if (player->getBoost())
	{
		float x = player->getSpaceship()->getX();
		float y = player->getSpaceship()->getY();
		drawingManager->DrawBoost(x, y);
		Mix_PlayChannel(-1, rocket, 0);
	}
}

void GameManager::renderWarp()
{
	if (player->isWarp())
	{
		drawingManager->DrawWarp(player->getWarpX(), elapsed);
	}
}

void GameManager::renderStartScreenAnimation()
{
	if (drawingManager->getStartScreenReady())
	{
		drawingManager->DrawStartScreen();
	}
	else
	{
		if (!drawingManager->getSWComplete())
		{
			drawingManager->SamWeissman();
		}
		else
		{
			if (!drawingManager->getPresentsComplete())
			{
				drawingManager->Presents();
			}
			else
			{
				if (!drawingManager->getSpaceInvadersComplete())
				{
					drawingManager->SpaceInvaders();
				}
				else
				{
					if (!drawingManager->getShowControlsComplete())
					{
						drawingManager->ShowControls();
					}
				}
			}
		}
	}
}

void GameManager::renderPlayerLostAnimation()
{
	Mix_PlayChannel(-1, alienLaugh, 0);
	drawingManager->DrawAlienFace(2);
	drawingManager->DrawYouLose(player->getScore());
}

void GameManager::clearScreen()
{
	glClearColor(clearRed, clearGreen, clearBlue, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GameManager::resetClearColors()
{
	clearRed = standardClearColor;
	clearBlue = standardClearColor;
	clearGreen = standardClearColor;
}

#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

void Game::init() {
	loading = true;
	bPlay = true;
	glClearColor(0.27f, 0.53f, 0.71f, 1.0f);
	initBackground();
	background();
	loopSound();
	playMainLoop();
	sceneMain = SceneMain();
	sceneBoss = SceneBoss();
	sceneTutorial = SceneTutorial();
	scene = &sceneTutorial;
	scene->init();
	loading = false;
}

void Game::helpGetOut() {
	scene->helpGetOut();
}

void Game::proceedToBoss() {
	if (scene == &sceneMain) {
		loading = true;
		background();
		sceneBoss.init(scene->getMainPlayer());
		scene = &sceneBoss;
		loading = false;
	}
}

void Game::proceedToGame() {
	if (scene == &sceneTutorial) {
		loading = true;
		background();
		sceneMain.init(scene->getMainPlayer());
		scene = &sceneMain;
		loading = false;
	}
}

bool Game::update(int deltaTime)
{
	scene->update(deltaTime);
	
	return bPlay;
}

void Game::render() {
	if (!loading) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene->background();
		scene->render();
	}
}

void Game::keyPressed(int key)
{
	pressedKey = key;
	if(key == 27) // Escape code
		scene->showMenu();
	else if (key == '1') scene->selectItem(0);
	else if (key =='2') scene->selectItem(1);
	else if (key == '3') scene->selectItem(2);
	else if (key == '4') scene->selectItem(3);
	else if (key == '5') scene->selectItem(4);
	else if (key == '6') scene->selectItem(5);
	else if (key == '7') scene->selectItem(6);
	else if (key == '8') scene->selectItem(7);
	else if (key == 'M' || key == 'm') scene->showMenu();
	else if (key == 'L' || key == 'l') scene->showAnastasio();
	else if (key == 'C' || key == 'c') scene->showCraftingMenu();
	else if(key!=32 && key != 'a' && key != 'A'&& key != 'w' && key != 'W'&& key != 'd' && key != 'D') scene->anyOtherKeyPressed();
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

void Game::mousePress(int x, int y)
{
	mouseX = x;
	mouseY = y;
	scene->mouseClicked(x, y);
}

void Game::mouseRelease(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

std::pair<int,int> Game::getMousePosition() {
	pair <int, int> position;
	position.first = mouseX;
	position.second = mouseY;
	return position;
}

std::pair<float, float> Game::getOffsetCamera() {
	return scene->getOffsetCamera();
}

int Game::getPressedKey() {
	return pressedKey;
}

void Game::loopSound() {
	FMOD::System_Create(&system);
	system->init(2, FMOD_INIT_NORMAL, NULL);
	system->createSound("sounds/mainLoop.wav", FMOD_2D, 0, &mainLoop);
	mainLoop->setMode(FMOD_LOOP_NORMAL);
	system->createSound("sounds/bossLoop.wav", FMOD_2D, 0, &bossLoop);
	bossLoop->setMode(FMOD_LOOP_NORMAL);
}

void Game::playBossLoop() {
	channel1->setPaused(true);
	system->playSound(bossLoop, 0, true, &channel2);
	channel2->setPaused(false);
}

void Game::playMainLoop() {
	channel2->setPaused(true);
	system->playSound(mainLoop, 0, true, &channel1);
	channel1->setPaused(false);
}
bool Game::dmgEnnemys(int dmg, glm::ivec2 dmgAt) {
	return scene->dmgEnnemys(dmg, dmgAt);
}

FMOD::System* Game::getSoundSystem() {
	return system;
}

void Game::killOgre(EnOgre* ogre) {
	scene->killOgre(ogre);
}


void Game::alertYesClicked() {
	scene->alertYesClicked();
}

void Game::alertNoClicked() {
	scene->alertNoClicked();
}
void Game::playerOut(bool resetPlayer) {
	playMainLoop();
	if (resetPlayer) {
		sceneMain = SceneMain();
		scene = &sceneMain;
		scene->init();
	}
	else {
		sceneMain = SceneMain();
		sceneMain.init(scene->getMainPlayer());
		scene = &sceneMain;
	}
}

void Game::noHP() {
	scene->playerOut();
}

void Game::gg() {
	scene->gg();
}

bool Game::isBossScene() {
	return scene->isBossScene();
}


bool Game::isTutorialScene() {
	return scene->isTutorialScene();
}



void Game::initBackground() {
	backgroundTexture.loadFromFile("images/loading.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backgroundTexture.setWrapS(GL_CLAMP_TO_EDGE);
	backgroundTexture.setWrapT(GL_CLAMP_TO_EDGE);
	backgroundTexture.setMinFilter(GL_NEAREST);
	backgroundTexture.setMagFilter(GL_NEAREST);
}

void  Game::background() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// background render

	glOrtho(0.0f, 1024.0, 512.0, 0.0, 0.0, 1.f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	backgroundTexture.use();
	//glBindTexture(GL_TEXTURE_2D, backgroundTexture);

	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0); glVertex2d(0.0, 0.0);
	glTexCoord2d(1.0, 0.0); glVertex2d(1024.0, 0.0);
	glTexCoord2d(1.0, 1.0); glVertex2d(1024.0, 512.0);
	glTexCoord2d(0.0, 1.0); glVertex2d(0.0, 512.0);
	glEnd();

	// foreground render - added code, not working
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_QUADS);
	glVertex2d(500.0, 400.0);
	glVertex2d(500.0, 500.0);
	glVertex2d(600.0, 400.0);
	glVertex2d(600.0, 500.0);
	glEnd();

	glutSwapBuffers();
}
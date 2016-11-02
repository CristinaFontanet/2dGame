#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

void Game::init()
{
	bPlay = true;
	glClearColor(0.27f, 0.53f, 0.71f, 1.0f);
	loopSound();
	sceneMain = SceneMain();
	sceneBoss = SceneBoss();
	sceneTutorial = SceneTutorial();
	scene = &sceneMain;

	scene->init();
}

void Game::proceedToBoss() {
	if (scene == &sceneMain) {
		sceneBoss.init(scene->getMainPlayer());
		scene = &sceneBoss;
	}
}

void Game::proceedToGame() {
	if (scene == &sceneTutorial) {
		sceneMain.init(scene->getMainPlayer());
		scene = &sceneMain;
	}
}

bool Game::update(int deltaTime)
{
	scene->update(deltaTime);
	
	return bPlay;
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene->background();
	scene->render();
}

void Game::keyPressed(int key)
{
	pressedKey = key;
	if(key == 27) // Escape code
		scene->showMenu();
	if (key == '1') scene->selectItem(0);
	if (key =='2') scene->selectItem(1);
	if (key == '3') scene->selectItem(2);
	if (key == '4') scene->selectItem(3);
	if (key == '5') scene->selectItem(4);
	if (key == '6') scene->selectItem(5);
	if (key == '7') scene->selectItem(6);
	if (key == '8') scene->selectItem(7);
	if (key == 'M' || key == 'm') scene->showMenu();
	if (key == 'L' || key == 'l') scene->showAnastasio();
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
	FMOD::Sound     *sound1;
	FMOD::Channel   *channel1 = 0;	
	FMOD::System_Create(&system);
	system->init(2, FMOD_INIT_NORMAL, NULL);
	system->createSound("sounds/mainLoop.wav", FMOD_2D, 0, &sound1);
	sound1->setMode(FMOD_LOOP_NORMAL);
	system->playSound(sound1, 0, true, &channel1);
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


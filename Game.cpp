#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.27f, 0.53f, 0.71f, 1.0f);
	scene.init();
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene.background();
	scene.render();
}

void Game::keyPressed(int key)
{
	pressedKey = key;
	if(key == 27) // Escape code
		bPlay = false;
	if (key == '1') scene.selectItem(0);
	if (key =='2') scene.selectItem(1);
	if (key == '3') scene.selectItem(2);
	if (key == '4') scene.selectItem(3);
	if (key == '5') scene.selectItem(4);
	if (key == '6') scene.selectItem(5);
	if (key == '7') scene.selectItem(6);
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

void Game::mousePress(int button, int x, int y)
{
	mouseX = x;
	mouseY = y;
	scene.mouseClicked(x, y);
}

void Game::mouseRelease(int button, int x, int y)
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
	return scene.getOffsetCamera();
}

int Game::getPressedKey() {
	return pressedKey;
}

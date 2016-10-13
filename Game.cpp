#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
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
	scene.render();
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	if (key == 'i' || key == 'I') scene.openInventory();
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

}

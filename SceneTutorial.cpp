
#include "SceneTutorial.h"
#include "Game.h"

#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI\RendererModules\Ogre\Renderer.h>
#include <CEGUI\RendererModules\OpenGL\GL3Renderer.h>
#include <GL/glut.h>

SceneTutorial::SceneTutorial() {
	map = NULL;
	mainPlayer = NULL;
	anastasio = NULL;
}

SceneTutorial::~SceneTutorial() {
	Scene::~Scene();
	if (anastasio != NULL) delete anastasio;
}

void SceneTutorial::init() {
	playerXtiles = 10;
	playerYtiles = 10;
	Scene::init("images/background.png", "levels/Tutorial.txt", glm::vec2(playerXtiles , playerYtiles) );

	anastasio = new Anastasio();
	anastasio->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, Anastasio::AnastasioType::TUTORIAL);
	anastasio->setTileMap(map);
	anastasio->setPosition(glm::vec2(offsetXCamera, offsetYCamera));
	anastasio->setTarget(mainPlayer);
	anastasio->startTutorial();
	projection = glm::ortho(0.f, float(tileSize*(map->getMapSize().x - 3)), float(tileSize*(map->getMapSize().x - 13)), 0.f);
	projection = glm::translate(projection, glm::vec3(-32, 10*tileSize, 0.f));
	menu_gui.showMenuClicked();
}

void SceneTutorial::update(int deltaTime) {
	Scene::update(deltaTime);

	//no cal fer update del mapa xq aquest no te animacions ni res 
	if(!menu_gui.isMenuShowing() && !showingAlert) {		//PAUSA si s'esta mostrant el menu
		if (anastasio->update(deltaTime)) {
			showingAlert = true;
			showAlert("Are you ready to proceed?");
		}
	}
	projection = glm::ortho(0.f, float(tileSize*(map->getMapSize().x - 3)), float(tileSize*(map->getMapSize().x - 13)), 0.f);
	projection = glm::translate(projection, glm::vec3(-32, 10*tileSize, 0.f));

}

void SceneTutorial::alertYesClicked() {
	showingAlert = false;
	Game::instance().proceedToGame();
}

void SceneTutorial::alertNoClicked() {
	showingAlert = false;
	anastasio->startTutorial();

}
void SceneTutorial::anyOtherKeyPressed() {
	if (!anastasio->nextText()) {
		showAlert("Are you ready to proceed?");
	}
}


bool SceneTutorial::render() {
	Scene::render();
	if(!menu_gui.isMenuShowing())anastasio->render();

	Scene::renderGUI();	//IMPORTAAANT, despres de tots els renders
	return true;
}

bool SceneTutorial::mouseClicked(int x, int y) {
	bool used = Scene::mouseClicked(x, y);
	if (!used) {
		if (!anastasio->nextText()) {
			showAlert("Are you ready to proceed?");
		}
	}
	return used;
}
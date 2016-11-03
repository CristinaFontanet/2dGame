#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneMain.h"
#include "Game.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI\RendererModules\Ogre\Renderer.h>
#include <CEGUI\RendererModules\OpenGL\GL3Renderer.h>
#include <GL/glut.h>

SceneMain::SceneMain() {
	map = NULL;
	mainPlayer = NULL;
	enemy = NULL;
	pony = NULL;
}

SceneMain::~SceneMain() {
	Scene::~Scene();
	if (enemy != NULL) delete enemy;
	if (pony != NULL) delete pony;
}
void SceneMain::init(MainPlayer* mPlayer) {
	init();
	Scene::combinePlayer(mPlayer);
}

void SceneMain::init() {
	playerXtiles = 1;
	playerYtiles = 107;

	Scene::init("images/background.png", "levels/levelTerraria300.txt",glm::vec2 (playerXtiles, playerYtiles));

	map->createCaveAt(57,109);
	enemy = new Enemy();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemy->setPosition(glm::vec2((playerXtiles+50) * map->getTileSize(), (playerYtiles-10) * map->getTileSize()));
	enemy->setTileMap(map);
	enemy->setTarget(mainPlayer);

	pony = new Enemy();
	pony->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	pony->setPosition(glm::vec2((playerXtiles+230) * map->getTileSize(), (playerYtiles-10) * map->getTileSize()));
	pony->setTileMap(map);
	pony->setTarget(mainPlayer);
	
	createOgres();
	menu_gui.showCraftButton(true);
}

void SceneMain::update(int deltaTime) {
	Scene::update(deltaTime);
	//no cal fer update del mapa xq aquest no te animacions ni res 
	if(!menu_gui.isMenuShowing() && !showingAlert) {		//PAUSA si s'esta mostrant el menu
		enemy->update(deltaTime);
		pony->update(deltaTime);
		updateOgres(deltaTime);
	}

}

bool SceneMain::render() {
	bool b = Scene::render();
	if (b) {
		enemy->render(); //linia blanca
		pony->render();	//linia blanca
		renderOgres();	//linia negre
	}
	Scene::renderGUI();	//IMPORTAAANT, despres de tots els renders
	return true;
}

void SceneMain::renderOgres() {
	if (ogres.size() > 0 ) {
		for each(EnOgre * ogre in ogres) {
			ogre->render();
		}
	}
}

void SceneMain::updateOgres(int deltaTime) {
	int inSize = ogres.size();
	if (ogres.size() >= 1) {
		for each(EnOgre * ogre in ogres) {
			ogre->update(deltaTime);
		}
		if (ogresToDelete.size() > 0) for each(EnOgre* ogreDelete in ogresToDelete) updateArrayOgres(ogreDelete);
		vector<EnOgre*> auxOg;
		ogresToDelete = auxOg;
	}
}

bool SceneMain::dmgEnnemys(int dmg, glm::ivec2 dmgAt ) {
	bool damaged = false;
	for each (EnOgre * ogre in ogres) {
		if (ogre->reciveDmg(dmg, dmgAt)) damaged = true;
	}
	return damaged;
}

void SceneMain::killOgre(EnOgre * ogre) {
	ogresToDelete.push_back(ogre);
}

void SceneMain::updateArrayOgres(EnOgre * ogre) {
	if (ogres.size() > 0) {
		vector<EnOgre*> auxOg;
		for each(EnOgre * og in ogres) {
			if (og != ogre) auxOg.push_back(og);
		}
		ogres = auxOg;
	}
}

void SceneMain::createOgres() {
	posOgres = map->getEnemiesPos();
	if (posOgres.size() > 0) {
		for each (glm::vec2 pos in posOgres) {
			ogre1 = new EnOgre();
			ogre1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			ogre1->setPosition(glm::vec2((pos.x)* map->getTileSize(), pos.y * map->getTileSize()));
			ogre1->setTileMap(map);
			ogre1->setTarget(mainPlayer);
			ogres.push_back(ogre1);
		}
	}
	
}

void SceneMain::playerOut() {
	showingAlert = true;
	showAlert("Do you want to continue?");
}

void SceneMain::alertYesClicked() {
	showingAlert = false;
	if (mainPlayer->getLives() > 0) {
		glm::vec2 currentPos = mainPlayer->getPlayerPosition();
		mainPlayer->setPosition(glm::vec2(currentPos.x-CAVE_WIDTH*map->getTileSize(), currentPos.y-CAVE_HEIGHT * map->getTileSize()));
		menu_gui.helpGetOut(false);
	}
	else Game::instance().playerOut(false);
}

void SceneMain::alertNoClicked() {
	if (mainPlayer->getLives() > 0) {
		showingAlert = false;
		menu_gui.helpGetOut(false);
	}
	else exit(0);
}
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
//	player = NULL;
	mainPlayer = NULL;
	enemy = NULL;
	pony = NULL;
}

SceneMain::~SceneMain() {
	Scene::~Scene();
	if (enemy != NULL) delete enemy;
	if (pony != NULL) delete pony;
}

void SceneMain::init() {
	Scene::init("images/background.png", "levels/levelTerraria300.txt");

/*	player = new P_conillet();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	//boss
	boss = new P_boss();
	boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	boss->setPosition(glm::vec2(INIT_BOSS_X_TILES * map->getTileSize(), INIT_BOSS_Y_TILES * map->getTileSize()));
	boss->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
*/

	enemy = new Enemy();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemy->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	enemy->setTileMap(map);
	enemy->setTarget(mainPlayer);
	
	
	ogre1 = new EnOgre();
	ogre1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	ogre1->setPosition(glm::vec2((10+INIT_PLAYER_X_TILES)* map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	ogre1->setTileMap(map);
	ogre1->setTarget(mainPlayer);

	ogres.push_back(ogre1);

	pony = new Enemy();
	pony->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	pony->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	pony->setTileMap(map);
	pony->setTarget(mainPlayer);
}

void SceneMain::update(int deltaTime) {
	Scene::update(deltaTime);
	//no cal fer update del mapa xq aquest no te animacions ni res 
	if(!menu_gui.isMenuShowing()) {		//PAUSA si s'esta mostrant el menu
		enemy->update(deltaTime);
		pony->update(deltaTime);
		updateOgres(deltaTime);
	}
}

void SceneMain::render() {
	Scene::render();

//	enemy->render(); //linia blanca
//	pony->render();	//linia blanca
//	renderOgres();	//linia negre
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
		if(ogre->reciveDmg(dmg,dmgAt)) damaged = true ;
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
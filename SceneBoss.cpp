
#include "SceneBoss.h"

SceneBoss::SceneBoss() {
	map = NULL;
	mainPlayer = NULL;
	boss = NULL;
}

SceneBoss::~SceneBoss() {
	Scene::~Scene();
	if (boss != NULL) delete boss;
}

void SceneBoss::init() {
	playerXtiles = 1;
	playerYtiles = 30;
	Scene::init("images/castillo.png", "levels/Castillo.txt",  glm::vec2(playerXtiles , playerYtiles) );

	//boss
	boss = new Boss();
	boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	boss->setPosition(glm::vec2((145) * map->getTileSize(), 35 * map->getTileSize()));
	boss->setTileMap(map);
	boss->setTarget(mainPlayer);

	createOgres();
}

void SceneBoss::update(int deltaTime) {
	Scene::update(deltaTime);
	//no cal fer update del mapa xq aquest no te animacions ni res 
	if(!menu_gui.isMenuShowing()) {		//PAUSA si s'esta mostrant el menu
		updateOgres(deltaTime);
		boss->update(deltaTime);
	}
}

void SceneBoss::render() {
	Scene::render();
	renderOgres();
	boss->render(); 
	Scene::renderGUI();	//IMPORTAAANT, despres de tots els renders
}

void SceneBoss::renderOgres() {
	if (ogres.size() > 0) {
		for each(EnOgre * ogre in ogres) {
			ogre->render();
		}
	}
}

void SceneBoss::updateOgres(int deltaTime) {
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

bool SceneBoss::dmgEnnemys(int dmg, glm::ivec2 dmgAt) {
	bool damaged = false;
	boss->reciveDmg(dmg, dmgAt);
	for each (EnOgre * ogre in ogres) {
		if (ogre->reciveDmg(dmg, dmgAt)) damaged = true;
	}
	return damaged;
}

void SceneBoss::killOgre(EnOgre * ogre) {
	ogresToDelete.push_back(ogre);
}

void SceneBoss::updateArrayOgres(EnOgre * ogre) {
	if (ogres.size() > 0) {
		vector<EnOgre*> auxOg;
		for each(EnOgre * og in ogres) {
			if (og != ogre) auxOg.push_back(og);
		}
		ogres = auxOg;
	}
}

void SceneBoss::createOgres() {
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
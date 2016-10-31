
#include "SceneBoss.h"
#include <glm/gtc/matrix_transform.hpp>


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

	bossStart = false;
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
	if (playerPos[0] / tileSize >= 130 && !bossStart) {
		bossStart = true;
		map->addMaterial(123 * tileSize, 36 * tileSize, playerPos[0], playerPos[1], LIM, 100);
		map->addMaterial(123*tileSize,35*tileSize,playerPos[0],playerPos[1],LIM,100);
		map->addMaterial(123 * tileSize, 34 * tileSize, playerPos[0], playerPos[1], LIM, 100);
		map->addMaterial(123 * tileSize, 33 * tileSize, playerPos[0], playerPos[1], LIM, 100);
	}

	//no cal fer update del mapa xq aquest no te animacions ni res 
	if(!menu_gui.isMenuShowing()) {		//PAUSA si s'esta mostrant el menu
		updateOgres(deltaTime);
		if (bossStart) {
			boss->update(deltaTime);
			projection = glm::ortho(0.f, float(800 - 1), float(600 - 1), 0.f);
			projection = glm::translate(projection, glm::vec3(124 * -tileSize , -680, 0.f));
			if (!boss->alive()) {
				projection = glm::ortho(0.f, float(800 - 1), float(600 - 1), 0.f);
				projection = glm::translate(projection, glm::vec3(124 * -tileSize, -200, 0.f));
			}
		}
	}
}

void SceneBoss::render() {
	Scene::render();
	renderOgres();
	if(bossStart)boss->render(); 
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
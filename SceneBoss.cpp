
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



void SceneBoss::init(MainPlayer* mPlayer) {
	playerXtiles = 1;
	playerYtiles = 20;
	Scene::init("images/background.png", "levels/Castillo.txt",  glm::vec2(playerXtiles , playerYtiles) );
	Scene::combinePlayer(mPlayer);
	//boss
	boss = new Boss();
	boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	boss->setPosition(glm::vec2((10 + playerXtiles) * map->getTileSize(), playerYtiles * map->getTileSize()));
	boss->setTileMap(map);
	boss->setTarget(mainPlayer);

}

void SceneBoss::update(int deltaTime) {
	Scene::update(deltaTime);
	//no cal fer update del mapa xq aquest no te animacions ni res 
	if(!menu_gui.isMenuShowing()) {		//PAUSA si s'esta mostrant el menu
		boss->update(deltaTime);
	}
}

void SceneBoss::render() {
	Scene::render();

	boss->render(); 
	Scene::renderGUI();	//IMPORTAAANT, despres de tots els renders
}

bool SceneBoss::dmgEnnemys(int dmg, glm::ivec2 dmgAt ) {
	bool damaged = false;
	
	//if (boss->reciveDmg(dmg, dmgAt)) damaged = true;
	
	return damaged;
}
/*
void SceneBoss::killOgre(EnOgre * ogre) {
	//ogresToDelete.push_back(ogre);
}

*/
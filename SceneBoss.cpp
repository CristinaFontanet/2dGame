
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
	Scene::init("images/background.png", "levels/Castillo.txt");

	//boss
	boss = new Boss();
	boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	boss->setPosition(glm::vec2((10 + INIT_PLAYER_X_TILES) * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
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
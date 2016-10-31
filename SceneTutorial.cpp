
#include "SceneTutorial.h"

SceneTutorial::SceneTutorial() {
	map = NULL;
	mainPlayer = NULL;
	ogre1 = NULL;
	pony = NULL;
}

SceneTutorial::~SceneTutorial() {
	Scene::~Scene();
	if (ogre1 != NULL) delete ogre1;
	if (pony != NULL) delete pony;
}

void SceneTutorial::init() {
	playerXtiles = 10;
	playerYtiles = 10;
	Scene::init("images/background.png", "levels/Tutorial.txt", glm::vec2(playerXtiles , playerYtiles) );

	ogre1 = new EnOgre();
	ogre1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	ogre1->setPosition(glm::vec2(playerXtiles * map->getTileSize(), playerYtiles * map->getTileSize()));
	ogre1->setTileMap(map);
	ogre1->setTarget(mainPlayer);

	pony = new Enemy();
	pony->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	pony->setPosition(glm::vec2(playerXtiles * map->getTileSize(), playerYtiles * map->getTileSize()));
	pony->setTileMap(map);
	pony->setTarget(mainPlayer);

}

void SceneTutorial::update(int deltaTime) {
	Scene::update(deltaTime);


	//no cal fer update del mapa xq aquest no te animacions ni res 
	if(!menu_gui.isMenuShowing() && !showingAlert) {		//PAUSA si s'esta mostrant el menu
		ogre1->update(deltaTime);
		pony->update(deltaTime);
	}
}

void SceneTutorial::render() {
	Scene::render();

	ogre1->render(); 
	pony->render();	

	Scene::renderGUI();	//IMPORTAAANT, despres de tots els renders
}

bool SceneTutorial::dmgEnnemys(int dmg, glm::ivec2 dmgAt ) {
	bool damaged = false;
	
	if (ogre1->reciveDmg(dmg, dmgAt)) damaged = true;
	
	return damaged;
}

void SceneTutorial::killOgre(EnOgre * ogre) {
	//ogresToDelete.push_back(ogre);
}


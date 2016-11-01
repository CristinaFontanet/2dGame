
#include "SceneTutorial.h"

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
	anastasio->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, false);
	anastasio->setPosition(glm::vec2(playerXtiles * map->getTileSize(), playerYtiles * map->getTileSize()));
	anastasio->setTileMap(map);
	anastasio->setTarget(mainPlayer);

}

void SceneTutorial::update(int deltaTime) {
	Scene::update(deltaTime);


	//no cal fer update del mapa xq aquest no te animacions ni res 
	if(!menu_gui.isMenuShowing() && !showingAlert) {		//PAUSA si s'esta mostrant el menu
		anastasio->update(deltaTime);
	}
}

void SceneTutorial::render() {
	Scene::render();

	anastasio->render();

	Scene::renderGUI();	//IMPORTAAANT, despres de tots els renders
}


#include "SceneTutorial.h"
#include "Game.h"

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
	glm::vec2 siz = map->getMapSize();
	anastasio->setPosition(glm::vec2(1370, 384));
	anastasio->setTileMap(map);
	anastasio->setTarget(mainPlayer);

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
}

void SceneTutorial::alertYesClicked() {
	std::cout << "YESS" << std::endl;
	showingAlert = false;
	Game::instance().proceedToGame();
}

void SceneTutorial::alertNoClicked() {
	std::cout << "Noo" << std::endl;
	showingAlert = false;
}

void SceneTutorial::render() {
	Scene::render();

	anastasio->render();

	Scene::renderGUI();	//IMPORTAAANT, despres de tots els renders
}

bool SceneTutorial::mouseClicked(int x, int y) {
	bool used = Scene::mouseClicked(x, y);
	if (!used) {
		return anastasio->nextText();
	}
	return used;
}
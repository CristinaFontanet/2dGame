#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI\RendererModules\Ogre\Renderer.h>
#include <CEGUI\RendererModules\OpenGL\GL3Renderer.h>
#include <GL/glut.h>


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 8
#define INIT_PLAYER_Y_TILES 107
#define INIT_BOSS_X_TILES 7
#define INIT_BOSS_Y_TILES 8

Scene::Scene() {
	map = NULL;
	player = NULL;
	boss = NULL;
	mainPlayer = NULL;
	enemy = NULL;
	pony = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if (boss != NULL)
		delete boss;
	if (mainPlayer != NULL) delete mainPlayer;
	if (enemy != NULL) delete enemy;
	if (pony != NULL) delete pony;
}

void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/levelTerraria300.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new P_conillet();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	//boss
	boss = new P_boss();
	boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	boss->setPosition(glm::vec2(INIT_BOSS_X_TILES * map->getTileSize(), INIT_BOSS_Y_TILES * map->getTileSize()));
	boss->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	//GUI
	m_gui.init("../GUI");
	Window* inventoryWindow = m_gui.getInventoryWindow();
	Window* livesWindow = m_gui.getLivesWindow();
	
	//Main Player
	mainPlayer = new MainPlayer();
	mainPlayer->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, inventoryWindow,livesWindow);
	mainPlayer->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	mainPlayer->setTileMap(map);
	playerPos = mainPlayer->getPlayerPosition();
	offsetXCamera = SCREEN_HEIGHT / 2 - playerPos[0];
	offsetYCamera = SCREEN_WIDTH / 2 - playerPos[1] * 1.025;
	projection = glm::translate(projection, glm::vec3(offsetXCamera, offsetYCamera, 0.f));
	
	enemy = new Enemy();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemy->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	enemy->setTileMap(map);
	enemy->setTarget(mainPlayer);

	pony = new Enemy();
	pony->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	pony->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	pony->setTileMap(map);
	pony->setTarget(mainPlayer);

	showingMenu = false;
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	//no cal fer update del mapa xq aquest no te animacions ni res 
	if(!showingMenu) {		//PAUSA si s'esta mostrant el menu
		currentTime += deltaTime;
		player->update(deltaTime);
		enemy->update(deltaTime);
		pony->update(deltaTime);
		mainPlayer->update(deltaTime);
		float incy, incx = 0;
		incy = playerPos[1] - mainPlayer->getPlayerPosition()[1];
		offsetYCamera += incy;
		if ((((playerPos[0]) - (SCREEN_WIDTH / 2)) >= 0) && (playerPos[0] < ((32 * 300) - (SCREEN_WIDTH / 2)))) {
			incx = playerPos[0] - mainPlayer->getPlayerPosition()[0];
			offsetXCamera += incx;
		}
		projection = glm::translate(projection, glm::vec3(incx, incy, 0.f));
		playerPos = mainPlayer->getPlayerPosition();
	}
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	enemy->render();
	mainPlayer->render();
	pony->render();
	m_gui.draw();
}

void Scene::showMenu() {
	showingMenu = !showingMenu;
	m_gui.setShowMenu(showingMenu);
}

void Scene::mouseClicked(int button, int x, int y) {
		if (!showingMenu)mainPlayer->mouseClick(x, y);
		else m_gui.mouseClick(x, y);
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}


void Scene::selectItem(int num) {
	if (!showingMenu) mainPlayer->equipItem(num);
}

std::pair<float, float> Scene::getOffsetCamera() {
	pair <float, float> offset;
	offset.first = -1 * offsetXCamera;
	offset.second = -1 * offsetYCamera;
	return offset;
}

void  Scene::background(){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f)
	gluOrtho2D(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	// Draw your quad here in screen coordinates
	glBegin(GL_QUADS);
		glColor3f(1,0,0);
		glVertex3f(0.0f, float(SCREEN_HEIGHT-1), 0.f);
		glColor3f(0, 1, 0);
		glVertex3f(float(SCREEN_WIDTH-1),float(SCREEN_HEIGHT-1), 0.f);
		glColor3f(1, 0, 0);
		glVertex3f(float(SCREEN_WIDTH-1),0.f, 0.f);
		glColor3f(1, 0, 0);
		glVertex3f(0.0f, 0.f, 0.f);
	glEnd();
	//end draw background quad 
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}


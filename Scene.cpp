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
	backgroundTexture.loadFromFile("images/background.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backgroundTexture.setWrapS(GL_CLAMP_TO_EDGE);
	backgroundTexture.setWrapT(GL_CLAMP_TO_EDGE);
	backgroundTexture.setMinFilter(GL_NEAREST);
	backgroundTexture.setMagFilter(GL_NEAREST);
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

	menu_gui.init("../GUI", mainPlayer,m_gui.getRenderer());

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
	currentTime = 0.0f;

	// Select which font you want to use
	if (!text.init("fonts/OpenSans-Regular.ttf"))
		//if(!text.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;
}

void Scene::update(int deltaTime)
{
	//no cal fer update del mapa xq aquest no te animacions ni res 
	if(!menu_gui.isMenuShowing()) {		//PAUSA si s'esta mostrant el menu
		currentTime += deltaTime;
		player->update(deltaTime);
		enemy->update(deltaTime);
		pony->update(deltaTime);
		updateOgres(deltaTime);
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
	text.render("Clica b per fer desaparèixer el text", glm::vec2(200, 200), 32, glm::vec4(0, 0.56, 0, 1));
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	enemy->render();
	pony->render();
	renderOgres();
	mainPlayer->render();
	m_gui.draw();
	menu_gui.draw();

	//Text
	string marcador = "Rebots: " + std::to_string(1);
	text.render(marcador, glm::vec2(glutGet(GLUT_WINDOW_HEIGHT)/2, glutGet(GLUT_WINDOW_WIDTH)/ 2), 200, glm::vec4(1, 1, 1, 1));
	text.render("Clica b per fer desaparèixer el text", glm::vec2(200, 200), 32, glm::vec4(0, 0.56, 0, 1));

}

void Scene::renderOgres() {
	if (ogres.size() > 0 ) {
		for each(EnOgre * ogre in ogres) {
			ogre->render();
		}
	}
}

void Scene::updateOgres(int deltaTime) {
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

void Scene::showMenu() {
	menu_gui.showMenuClicked();
}

void Scene::mouseClicked(int x, int y) {
	if (!menu_gui.isMenuShowing())mainPlayer->mouseClick(x, y);
	else menu_gui.mouseClick(x, y);
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
	if (!menu_gui.isMenuShowing()) mainPlayer->equipItem(num);
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

	backgroundTexture.use();

	glBegin(GL_QUADS);
		glTexCoord2f(0+0.05, 1);
		glVertex3f(0.0f, float(SCREEN_HEIGHT-1), 0.f);

		glTexCoord2f(1-0.05, 1);
		glVertex3f(float(SCREEN_WIDTH-1),float(SCREEN_HEIGHT-1), 0.f);

		glTexCoord2f(1-0.05, 0);
		glVertex3f(float(SCREEN_WIDTH-1),0.f, 0.f);

		glTexCoord2f(0+0.05, 0);
		glVertex3f(0.0f, 0.f, 0.f);
	glEnd();
	//end draw background quad 
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}


bool Scene::dmgEnnemys(int dmg, glm::ivec2 dmgAt ) {
	bool damaged = false;
	for each (EnOgre * ogre in ogres) {
		if(ogre->reciveDmg(dmg,dmgAt)) damaged = true ;
	}
	return damaged;
}

void Scene::killOgre(EnOgre * ogre) {
	ogresToDelete.push_back(ogre);
}

void Scene::updateArrayOgres(EnOgre * ogre) {
	if (ogres.size() > 0) {
		vector<EnOgre*> auxOg;
		for each(EnOgre * og in ogres) {
			if (og != ogre) auxOg.push_back(og);
		}
		ogres = auxOg;
	}
}
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

Scene::Scene() {
	map = NULL;
	mainPlayer = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if (mainPlayer != NULL) delete mainPlayer;
}

void Scene::init(string background, string level) {
	initShaders();
	backgroundTexture.loadFromFile(background, TEXTURE_PIXEL_FORMAT_RGBA);
	backgroundTexture.setWrapS(GL_CLAMP_TO_EDGE);
	backgroundTexture.setWrapT(GL_CLAMP_TO_EDGE);
	backgroundTexture.setMinFilter(GL_NEAREST);
	backgroundTexture.setMagFilter(GL_NEAREST);

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	map = TileMap::createTileMap(level, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

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

	currentTime = 0.0f;

	//boss
	boss = new Boss();
	boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	boss->setPosition(glm::vec2((10 + INIT_PLAYER_X_TILES) * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	boss->setTileMap(map);
	boss->setTarget(mainPlayer);

	currentTime = 0.0f;

}

void Scene::update(int deltaTime) {
	//no cal fer update del mapa xq aquest no te animacions ni res 
	if (!menu_gui.isMenuShowing()) {		//PAUSA si s'esta mostrant el menu
		currentTime += deltaTime;

		boss->update(deltaTime);
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

void Scene::renderGUI() {
	m_gui.draw();
	menu_gui.draw();
}

void Scene::render() {
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();

	boss->render();
	mainPlayer->render();

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

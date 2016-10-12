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

#include <include\SDL.h>
#include <include\SDL_timer.h>
#include <include\SDL_events.h>

#include  "CEGUI\RendererModules\OpenGL\GLRenderer.h"
#include <GL/gl.h>


#include <iostream>

using namespace std;

using namespace CEGUI;
#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 8
#define INIT_PLAYER_Y_TILES 7
#define INIT_BOSS_X_TILES 7
#define INIT_BOSS_Y_TILES 8

Scene::Scene() {
	map = NULL;
	player = NULL;
	boss = NULL;
	mainPlayer = NULL;
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

	//Main Player
	mainPlayer = new MainPlayer();
	mainPlayer->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	mainPlayer->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	mainPlayer->setTileMap(map);
	playerPos = mainPlayer->getPlayerPosition();
	offsetXCamera = SCREEN_HEIGHT / 2 - playerPos[0];
	offsetYCamera = SCREEN_WIDTH / 2 - playerPos[1] * 1.5;
	projection = glm::translate(projection, glm::vec3(offsetXCamera, offsetYCamera, 0.f));

	currentTime = 0.0f;

	//GUI
	
	m_gui.init("../GUI");
	m_gui.setFont("DejaVuSans-10");
	m_gui.setMouseCursor("TaharezLook/MouseArrow");
	m_gui.showMouseCursor();
	//
	//SDL_Window & screen = init_SDL();
	//SDL_ShowCursor(0);
}

void Scene::update(int deltaTime)
{
	//no cal fer update del mapa xq aquest no te animacions ni res 
	currentTime += deltaTime;
	player->update(deltaTime);
//	boss->update(deltaTime);
	mainPlayer->update(deltaTime);
	float incy, incx= 0;
	incy = playerPos[1] - mainPlayer->getPlayerPosition()[1];
	offsetYCamera += incy;
	if ((((playerPos[0]) - (SCREEN_WIDTH / 2)) >= 0) && (playerPos[0] < ((32 * 300) - (SCREEN_WIDTH / 2)))) {
		incx= playerPos[0] - mainPlayer->getPlayerPosition()[0];
		offsetXCamera += incx;
	}
	projection = glm::translate(projection, glm::vec3(incx, incy, 0.f));
	playerPos = mainPlayer->getPlayerPosition();
	checkInput();
}


void Scene::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
			//	m_game->onSDLEvent(evnt);
		m_gui.onSDLEvent(evnt);
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
	mainPlayer->render();
	m_gui.draw();

	// Updates the screen:
//	SDL_GL_SwapBuffers();
}


void Scene::mouseClicked(int x, int y) {
	mainPlayer->mouseClick(x, y);
}

void Scene::openInventory() {
	m_gui.createInventory( glm::vec4(0.5f, 0.5f, 0.1f, 0.5f), glm::vec4(0.0f), "Test Button");
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

std::pair<float, float> Scene::getOffsetCamera() {
	pair <float, float> offset;
	offset.first = abs(offsetXCamera);
	offset.second = abs(offsetYCamera);
	return offset;
}


SDL_Window & Scene::init_SDL()
{

	cout << " - initializing SDL" << endl;

	atexit(SDL_Quit);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cerr << "Unable to initialise SDL: " << SDL_GetError();
		exit(0);
	}
	SDL_Window *screen = SDL_CreateWindow("My Game Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1920, 1080,
		SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);

	//SDL_Surface * screen = SDL_SetVideoMode(600, 480, 0, SDL_HWSURFACE);

	if (screen == 0)
	{
		cerr << "Unable to set OpenGL videomode: " << SDL_GetError();
		SDL_Quit();
		exit(0);
	}

	SDL_ShowCursor(SDL_DISABLE);
	//	SDL_EnableUNICODE(1);
	//	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	return *screen;

}
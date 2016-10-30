#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "P_conillet.h"
#include "P_boss.h"
#include "MainPlayer.h"
#include "Enemy.h"
#include "Ogre.h"
#include "GUI.h"
#include "MenuGUI.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 8
#define INIT_PLAYER_Y_TILES 107
#define INIT_BOSS_X_TILES 7
#define INIT_BOSS_Y_TILES 8
// Scene contains all the entities of our game.
// It is responsible for updating and render them.
class Scene {

public:
	Scene();
	~Scene();
	virtual void init() = 0;
	virtual void render();
	virtual void update(int deltaTime);

	void init(string background,string level);
	void initShaders();
	void background();
	void mouseClicked(int x, int y);
	void showMenu();
	std::pair<float, float> getOffsetCamera();
	void selectItem(int num);


	virtual bool dmgEnnemys(int dmg, glm::ivec2 dmgAt) = 0;
	virtual void killOgre(EnOgre * ogre)=0;
protected:
	TileMap *map;
	MainPlayer *mainPlayer;
	bool showingMenu;
	ShaderProgram texProgram;
	float currentTime;
	OwnTexture backgroundTexture;
	glm::vec2 playerPos;
	glm::mat4 projection;
	float offsetXCamera, offsetYCamera;
	Bengine::GUI m_gui;
	MenuGUI menu_gui;
};

#endif // _SCENE_INCLUDE


#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "MainPlayer.h"
#include "Enemy.h"
#include "Ogre.h"
#include "Boss.h"
#include "GUI.h"
#include "MenuGUI.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include "AlertGUI.h"

#define INIT_BOSS_X_TILES 7
#define INIT_BOSS_Y_TILES 8
// Scene contains all the entities of our game.
// It is responsible for updating and render them.
class Scene {

public:
	Scene();
	~Scene();
	void init(string background, string level, glm::vec2 initPosPlayer);
	virtual void init() {};
	virtual bool render();
	virtual void update(int deltaTime);
	virtual void alertYesClicked();
	virtual void alertNoClicked();

	virtual void playerOut() {};
	void helpGetOut();
	void initShaders();
	void background();
	virtual bool mouseClicked(int x, int y);
	virtual void showMenu();
	std::pair<float, float> getOffsetCamera();
	void selectItem(int num);
	MainPlayer* getMainPlayer();
	void showAlert(string text);

	virtual bool dmgEnnemys(int dmg, glm::ivec2 dmgAt) { return false; };
	virtual void killOgre(EnOgre * ogre) {};
	virtual void gg() {};
	void combinePlayer(MainPlayer* mPlayer);
	virtual void showAnastasio();
	virtual bool isBossScene() { return false; }
	virtual bool isTutorialScene() { return false; }

	virtual void anyOtherKeyPressed() {};
	virtual void showCraftingMenu() {};
protected:
	virtual void renderGUI();
	TileMap *map;
	MainPlayer *mainPlayer;
	bool showingMenu;
	int minXOffset, minYOffset,tileSize;
	glm::vec2 mapSize;

	ShaderProgram texProgram;
	float currentTime;
	OwnTexture backgroundTexture;
	glm::vec2 playerPos;
	glm::mat4 projection;
	float offsetXCamera, offsetYCamera;
	Bengine::GUI m_gui;
	MenuGUI menu_gui;

	bool showingAlert;
	AlertGUI al;

};

#endif // _SCENE_INCLUDE


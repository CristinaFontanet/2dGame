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

	void helpGetOut();
	void initShaders();
	void background();
	void selectItem(int num);
	void showAlert(string text);
	void combinePlayer(MainPlayer* mPlayer);

	/** Virtuals*/
	virtual void alertYesClicked();
	virtual void alertNoClicked();
	virtual void playerOut() {};
	virtual void showAnastasio();
	virtual bool mouseClicked(int x, int y);
	virtual void showMenu();
	virtual void anyOtherKeyPressed() {};
	virtual void showCraftingMenu() {};
	virtual void killOgre(EnOgre * ogre) {};
	virtual void gg() {};
	virtual bool dmgEnnemys(int dmg, glm::ivec2 dmgAt) { return false; };

	/** Getters */
	virtual bool isBossScene() { return false; }
	virtual bool isTutorialScene() { return false; }
	MainPlayer* getMainPlayer();
	std::pair<float, float> getOffsetCamera();

protected:
	virtual void renderGUI();
	bool showingMenu;
	int minXOffset, minYOffset,tileSize;
	float offsetXCamera, offsetYCamera;
	float currentTime;
	glm::vec2 mapSize;
	glm::vec2 playerPos;
	OwnTexture backgroundTexture;
	glm::mat4 projection;
	ShaderProgram texProgram;
	Bengine::GUI m_gui;
	MenuGUI menu_gui;
	TileMap *map;
	MainPlayer *mainPlayer;

	bool showingAlert;
	AlertGUI al;

};

#endif // _SCENE_INCLUDE


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

// Scene contains all the entities of our game.
// It is responsible for updating and render them.
class Scene {

public:
	Scene();
	~Scene();
	virtual void init() = 0;
	void init(string background,string level);

	virtual void update(int deltaTime);
	virtual void render();
	virtual void renderOgres();
	void updateOgres(int deltaTime);
	void mouseClicked(int x, int y);
	void background();
	bool dmgEnnemys(int dmg, glm::ivec2 dmgAt);
	void killOgre(EnOgre * ogre);
	void updateArrayOgres(EnOgre * ogre);
	void selectItem(int num);
	void showMenu();
	std::pair<float, float> getOffsetCamera();

	void updateOgres(EnOgre * ogre);
	void initShaders();

protected:
	TileMap *map;
	MainPlayer *mainPlayer;
	EnOgre *ogre1;
	Enemy *enemy;
	Enemy *pony;
	bool showingMenu;
	P_conillet *player;
	P_boss *boss;
	ShaderProgram texProgram;
	float currentTime;
	OwnTexture backgroundTexture;
	glm::vec2 playerPos;
	glm::mat4 projection;
	float offsetXCamera, offsetYCamera;
	vector<EnOgre*> ogres;
	Bengine::GUI m_gui;
	MenuGUI menu_gui;
	vector<EnOgre*> ogresToDelete;
};

#endif // _SCENE_INCLUDE


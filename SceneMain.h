#ifndef _SCENE_MAIN_INCLUDE
#define _SCENE_MAIN_INCLUDE

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
#include "Text.h"
#include "Scene.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.
class SceneMain: public Scene {

public:
	SceneMain();
	~SceneMain();

	virtual void init();
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

protected:
	EnOgre *ogre1;
	Enemy *enemy;
	Enemy *pony;
	//P_conillet *player;
	P_boss *boss;
	vector<EnOgre*> ogres;
	Text text;
	vector<EnOgre*> ogresToDelete;

};


#endif // _SCENE_INCLUDE

